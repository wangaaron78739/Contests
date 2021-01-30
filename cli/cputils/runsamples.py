#!/usr/bin/env python3

import click
import io
import os
import unittest

# class RunSamplesMethods(unittest.TestCase):
#     testPath = "a.txt"
#     refPath = "a.in"
#     def test_sameFiles(self):
#         with io.open(testPath, "r") as testFile:
#             with io.open(refPath, "r") as refFile:
#                 self.assertListEqual(list(testFile), list(refFile))

@click.command()
@click.argument("filename", nargs=1)
def main(filename):
    os.system(f"g++ {filename}.cpp -o {filename}.out")
    # unittest.main(argv=['first-arg-is-ignored'],module=__name__)

