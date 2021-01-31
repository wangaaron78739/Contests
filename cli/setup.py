#!/usr/bin/env python3

from setuptools import setup

with open("README.md") as f:
    readme = f.read()

setup(
    name="cputils",
    version="0.0.1",
    author="Aaron Wang",
    long_description=readme,
    long_description_content_type="text/markdown",
    licence="MIT",
    package=["cputils"],
    package_data={"": ["../../libs/*.cpp"]},
    include_package_data=True,
    python_requires=">=3.7",
    entry_points = {
        "console_scripts": ["codeforces_gen=cputils.codeforces_gen:main",
                            "runsamples=cputils.runsamples:main",
                            "dbrun=cputils.dbrun:main",
                            "cf_sample_gen=cputils.cf_sample_gen:main",
                            ],
    },
    install_requires=["click","rich", "requests", "beautifulsoup4"],
    
)
