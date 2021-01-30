#!/usr/bin/env python3

from setuptools import setup, find_packages

with open("README.md") as f:
    readme = f.read()

setup(
    name="cputils",
    version="0.0.1",
    author="Aaron Wang",
    long_description=readme,
    long_description_content_type="text/markdown",
    licence="MIT",
    packages=find_packages(include="cputils"),
    package_data={"": ["../libs/*.cpp"]},
    entry_points={
        "console_script": [
            "codeforces_gen=cputils.codeforces_gen:codeforces_gen"
        ]
    }
)
