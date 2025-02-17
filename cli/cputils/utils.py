#!/usr/bin/env python3

from rich.console import Console
from rich.panel import Panel


class ConsoleUtils(Console):
    def __init__(self) -> None:
        super().__init__()

    def error(self, message: str) -> None:
        self.print(f"ERROR: {message}", style="bold red")

    def message(self, message: str, style: str) -> None:
        self.print(f"{message}", style=style)


def apply_style(message: str, style: str) -> str:
    return f"[{style}]{message}[/{style}]"


class LivePanel(Panel):
    title: str
    title_message: str
    message: str
    renderable: str

    def __init__(
        self, title: str, highlight: bool = True, expand: bool = False
    ) -> None:
        super().__init__(
            "", title=f"[bold green]{title}", highlight=highlight, expand=expand
        )
        self.title_message = title
        self.message = ""

    def add(self, message: str) -> None:
        self.message += f"{message}\n"
        self.renderable = self.message.strip()

    def add_error(self, message: str) -> None:
        self.add(apply_style(f"{message}", "bold red"))
        self.title = f"[bold red]{self.title_message}"
