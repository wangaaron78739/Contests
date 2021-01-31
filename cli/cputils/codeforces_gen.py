#!/usr/bin/env python3

import click
from rich import print
from rich.live import Live
from cputils.utils import LivePanel
import pkg_resources
import os
import shutil

@click.command()
@click.option("-c","--cases", is_flag=True)
@click.argument("filenames", nargs=-1)
def main(cases, filenames):

    panel = LivePanel("Generating Codeforces Template Files")
    with Live(panel, refresh_per_second = 10):
        try:
            template_file = pkg_resources.resource_filename(__name__,"../../libs/cf_template_cases.cpp") if cases \
                            else pkg_resources.resource_filename(__name__,"../../libs/cf_template.cpp")
            for filename in [f+".cpp" for f in filenames]:
                shutil.copyfile(template_file,filename)
                panel.add(f"Generated {filename}{' with cases' if cases else ''}.")
            panel.add("Done.")
            if not os.path.exists("samples"):
                panel.renderable += f"Created samples directory.\n"
                os.makedirs("samples")
        except Exception as err:
            panel.add_error(f"{err}.")

