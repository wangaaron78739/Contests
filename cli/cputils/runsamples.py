#!/usr/bin/env python3

import click
import io
import os
import glob
import time
import datetime
from rich import print, box
from cputils.utils import ConsoleUtils, apply_style
from rich.table import Table
from rich.panel import Panel
from rich.live import Live
from enum import Enum, IntEnum
import itertools


console = ConsoleUtils()


class COLUMNS(IntEnum):
    NAME = (0,)
    INPUT = (1,)
    EXPECTED = (2,)
    OUTPUT = (3,)
    MISMATCH = (4,)
    TIME = (5,)
    RESULT = 6


class RESULT(Enum):
    PASSED = "[bold green]PASSED"
    FAILED = "[bold red]FAILED"


class ResultTable:
    DEFAULT_ROW = ["N/A"] * len(COLUMNS)

    def __init__(self, test_count):
        self.table_data = {}
        self.built = False

    def add_test(self, test_name):
        self.table_data[test_name] = ResultTable.DEFAULT_ROW.copy()
        self.table_data[test_name][COLUMNS.NAME] = test_name
        self.built = False

    def build(self):
        self.table = Table(
            show_header=True, header_style="bold magenta", box=box.SQUARE
        )
        for col in COLUMNS:
            self.table.add_column(col.name)

        for entry in self.table_data.values():
            self.table.add_row(*entry)

        self.built = True
        return self.table

    def print(self):
        if not self.built:
            self.build()
        console.print(self.table)

    def add(self, test_name, attr, value):
        self.table_data[test_name][attr] = value
        self.built = False


def highlight_diff(line, same):
    return f"{'' if same else '[bold red]'}{line}{'' if same else '[/bold red]'}"


@click.command()
@click.argument("filename", nargs=1)
@click.option("--nocompile", is_flag=True, default=False)
@click.option("--nodebug", is_flag=True, default=False)
def main(filename, nocompile, nodebug):
    if not os.path.exists(filename + ".cpp"):
        console.error(f"{filename}.cpp not found.")
        return
    if not nocompile:
        console.print(
            f"[bold yellow][{'PROD' if nodebug else 'DEBUG'} MODE][/bold yellow] Compiling {filename}.cpp with c++17"
        )
        if (
            os.system(
                f"g++ {filename}.cpp -o samples/{filename} -std=gnu++17 {'' if nodebug else '-DAARON_DEBUG'}"
            )
            != 0
        ):
            console.error(f"Compilation failed for {filename}.")
            return

    root_dir = os.getcwd()
    os.chdir(root_dir + "/samples")

    input_files = sorted(glob.glob(f"{filename}*.in"))
    output_files = sorted(glob.glob(f"{filename}*.out"))

    if {f for f in map(lambda x: x[:-3], input_files)} != {
        f for f in map(lambda x: x[:-4], output_files)
    }:
        console.error(f"Input and output files do not match.")
        return

    success_count = 0
    test_count = len(input_files)

    result_table = ResultTable(test_count)
    with Live(console=console, refresh_per_second=10) as live:

        for input_filename, output_filename in zip(input_files, output_files):
            run_filename = f"run_{output_filename}"
            result_table.add_test(input_filename)

            start_time = time.perf_counter()
            # TODO: First test includes compilation time for some reason
            if os.system(f"./{filename} < {input_filename} > {run_filename}") != 0:
                console.error(f"Process return non zero exit status.")
                result_table.add(input_filename, COLUMNS.RESULT, RESULT.FAILED.value)
                continue

            execution_time = time.perf_counter() - start_time
            result_table.add(input_filename, COLUMNS.TIME, f"{execution_time:.3f}s")

            with open(input_filename, "r") as in_file, open(
                run_filename, "r"
            ) as run_file, open(output_filename, "r") as out_file:
                result_table.add(input_filename, COLUMNS.INPUT, in_file.read().strip())

                run_lines = run_file.readlines()
                out_lines = out_file.readlines()

                diff = [
                    a.strip() == b.strip()
                    for a, b in itertools.zip_longest(
                        run_lines, out_lines, fillvalue=""
                    )
                ]
                passed = all(diff)
                result_table.add(
                    input_filename,
                    COLUMNS.OUTPUT,
                    "".join(map(lambda x: highlight_diff(*x), zip(run_lines, diff))),
                )
                result_table.add(
                    input_filename,
                    COLUMNS.EXPECTED,
                    "".join(map(lambda x: highlight_diff(*x), zip(out_lines, diff))),
                )
                if not passed:
                    min_len = min(len(run_lines), len(out_lines))
                    result_table.add(
                        input_filename,
                        COLUMNS.MISMATCH,
                        "\n".join(
                            map(
                                lambda idx: f"Line {idx}: expected: {run_lines[idx].strip()} output: {out_lines[idx].strip()}",
                                [
                                    i
                                    for i, x in enumerate(diff)
                                    if not x and i < min_len
                                ],
                            )
                        ),
                    )

                success_count += passed
                result_table.add(
                    input_filename,
                    COLUMNS.RESULT,
                    RESULT.PASSED.value if passed else RESULT.FAILED.value,
                )

            live.update(result_table.build())

    console.print(
        Panel(
            f"{success_count} / {test_count} tests passed.",
            title=apply_style(
                f"{filename} - Test Cases {'Passed' if success_count == test_count else 'Failed'}",
                "bold green" if success_count == test_count else "bold red",
            ),
            expand=False,
        )
    )
