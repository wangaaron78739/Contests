#!/usr/bin/env python3

import click
import os
import requests
from bs4 import BeautifulSoup
from cputils.utils import ConsoleUtils
from rich.panel import Panel
from rich.panel import Panel

@click.command()
@click.argument("contest_id", nargs=1, type=click.INT)
def main(contest_id: int):

    console = ConsoleUtils()
    panel = Panel(f"", title="[red]Generating Codeforces Template Files", highlight=True, expand=False)
    if not os.path.exists("samples"):
        panel.renderable += f"Created samples directory.\n"
        os.makedirs("samples")

    response = requests.get(f"https://codeforces.com/contest/{contest_id}/problems")
    soup = BeautifulSoup(response.content, "html.parser")
    problems = soup.find_all("div", class_="problemindexholder")
    console.print(panel)

    for problem in problems:
        problem_id = problem["problemindex"].lower()
        sample_inputs = map(lambda x: x.find("pre").contents[0], problem.find_all("div", class_="input"))
        sample_outputs = map(lambda x: x.find("pre").contents[0], problem.find_all("div", class_="output"))
        for idx, (inp, out) in enumerate(zip(sample_inputs, sample_outputs)):
            filename = f"{problem_id}-{idx}"
            with open(f"samples/{filename}.in", "w") as infile, open(f"samples/{filename}.out", "w") as outfile:
                infile.write(inp.strip())
                outfile.write(out.strip())
        panel.renderable += f"Done."
        console.clear()
        console.print(panel)

    console.print(panel)
