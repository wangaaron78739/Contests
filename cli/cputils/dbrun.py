#!/usr/bin/env python3

import click
import os
from cputils.utils import ConsoleUtils

console = ConsoleUtils()


@click.command()
@click.argument("filename", nargs=1)
@click.option("--nocompile", is_flag=True, default=False)
@click.option("--nodebug", is_flag=True, default=False)
def main(filename: str, nocompile: bool, nodebug: bool):
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

    console.message(f"Executing {filename}...", style="bold yellow")

    exit_value = os.system(f"./samples/{filename}")
    console.message(
        f"Program exited with {exit_value} exit status.",
        style="bold red" if exit_value else "bold green",
    )
