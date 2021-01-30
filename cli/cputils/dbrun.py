#!/usr/bin/env python3

import click
import os
from rich import print
from rich.console import Console

console = Console()

def error(message):
    console.print(f"ERROR: {message}", style = "bold red")

def message(message, style):
    console.print(f"{message}", style = style)

@click.command()
@click.argument("filename", nargs=1)
@click.option("--nocompile", is_flag=True, default=False)
@click.option("--nodebug", is_flag=True, default=False)
def main(filename, nocompile, nodebug):
    if not os.path.exists(filename+'.cpp'):
        error(f"{filename}.cpp not found.")
        return
    if not nocompile:
        console.print(f"[bold yellow][{'PROD' if nodebug else 'DEBUG'} MODE][/bold yellow] Compiling {filename}.cpp with c++17")
        if os.system(f"g++ {filename}.cpp -o samples/{filename} -std=gnu++17 {'' if nodebug else '-DAARON_DEBUG'}") != 0:
            error(f"Compilation failed for {filename}.")
            return

    message(f"Executing {filename}...", style="bold yellow")

    exit_value = os.system(f"./samples/{filename}")
    message(f"Program exited with {exit_value} exit status.", style="bold red" if exit_value else "bold green")
