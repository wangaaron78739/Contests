#!/usr/bin/env python3

import click
import os
import requests
from bs4 import BeautifulSoup
from cputils.utils import LivePanel
from rich.live import Live
from rich import live

@click.command()
@click.argument("contest_id", nargs=1, type=click.INT)
def main(contest_id: int):

    panel = LivePanel(f"Scraping Codeforces Contest with ID {contest_id}")
    with Live(panel, refresh_per_second=10):
        try:
            if not os.path.exists("samples"):
                panel.add("Samples directory not found.\nCreating samples directory.")
                os.makedirs("samples")

            contest_url = f"https://codeforces.com/contest/{contest_id}/problems"
            panel.add(f"Requesting from {contest_url}.")

            response = requests.get(contest_url)
            if response.status_code != 200:
                raise Exception(f"Recieved {response.status_code} Response")

            soup = BeautifulSoup(response.content, "html.parser")
            problems = soup.find_all("div", class_="problemindexholder")

            if len(problems) == 0:
                raise Exception(f"No Problems found")
                

            for problem in problems:
                problem_id = problem["problemindex"].lower()
                panel.add(f"Parsing problem {problem_id}.")
                sample_inputs = map(lambda x: x.find("pre").contents[0], problem.find_all("div", class_="input"))
                sample_outputs = map(lambda x: x.find("pre").contents[0], problem.find_all("div", class_="output"))
                for idx, (inp, out) in enumerate(zip(sample_inputs, sample_outputs)):
                    filename = f"{problem_id}-{idx}"
                    with open(f"samples/{filename}.in", "w") as infile, open(f"samples/{filename}.out", "w") as outfile:
                        infile.write(inp.strip())
                        outfile.write(out.strip())
        except Exception as err:
            panel.add_error(f"{err}.")

