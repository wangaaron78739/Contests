#!/usr/bin/env python3

from rich.console import Console
from rich.panel import Panel

class ConsoleUtils(Console):
    def __init__(self):
        super().__init__()

    def error(self, message):
        self.print(f"ERROR: {message}", style = "bold red")

    def message(self, message, style):
        self.print(f"{message}", style = style)

def apply_style(message, style):
    return f"[{style}]{message}[/{style}]"

class LivePanel(Panel):
    def __init__(self, title, highlight = True, expand = False):
        super().__init__(f"", title=f"[bold green]{title}", highlight=highlight, expand=expand)
        self.title_message = title
        self.message = ""

    def add(self, message):
        self.message += f"{message}\n"
        self.renderable = self.message.strip()

    def add_error(self, message):
        self.add(apply_style(f"{message}", "bold red"))
        self.title = f"[bold red]{self.title_message}"
