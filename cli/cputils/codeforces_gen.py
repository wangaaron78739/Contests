#!/usr/bin/env python3

import argparse
import shutil
import os

def codeforces_gen():
    parser = argparse.ArgumentParser()
    parser.add_argument('-c', '--cases',
                        action='store_true',
                        help='generate cases template for codeforces')
    parser.add_argument('filenames',
                        nargs='*',
                        help='filenames to be created')
    args = parser.parse_args()

    for filename in list(map(lambda x: x+'.cpp',args.filenames)):
        if args.cases:
            print('getcwd:',os.getcwd())
            print('__file__', __file__)
            # shutil.copyfile()
            print("have cases")
        else:
            # shutil.copyfile()
            print("no cases")
