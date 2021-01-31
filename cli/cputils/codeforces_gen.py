#!/usr/bin/env python3

import click
from rich import print
from rich.panel import Panel
import pkg_resources
import os
import shutil

@click.command()
@click.option("-c","--cases", is_flag=True)
@click.argument("filenames", nargs=-1)
def main(cases, filenames):

    panel = Panel(f"", title="[red]Generating Codeforces Template Files", highlight=True, expand=False)

    try:
        template_file = pkg_resources.resource_filename(__name__,"../../libs/cf_template_cases.cpp") if cases \
                        else pkg_resources.resource_filename(__name__,"../../libs/cf_template.cpp")
        for filename in [f+".cpp" for f in filenames]:
            shutil.copyfile(template_file,filename)
            panel.renderable += f"Generated {filename}{' with cases' if cases else ''}.\n"
        panel.renderable += f"Done."
        if not os.path.exists("samples"):
            panel.renderable += f"Created samples directory.\n"
            os.makedirs("samples")
    except:
        panel.renderable += f"[red] Error occured during generation."
    print(panel)

