#!/usr/bin/env python3

from rich.console import Console

class ConsoleUtils(Console):
    def __init__(self):
        super().__init__()

    def error(self, message):
        self.print(f"ERROR: {message}", style = "bold red")

    def message(self, message, style):
        self.print(f"{message}", style = style)

def apply_style(message, style):
    return f"[{style}]{message}[/{style}]"
