# -*- coding: utf-8 -*-

import os
import sys
import filecmp
import difflib
from subprocess import call

def run_test(fmt, sample, arg):
    psdump = "../build/psdump -o temp -f {0} {1}".format(fmt, arg)

    call(psdump.split())

    with open("temp", "r") as temp_file:
        temp_lines = temp_file.readlines()

    with open(sample, "r") as sample_file:
        sample_lines = sample_file.readlines()

    # Compare corresponding lines from 'temp' and 'sample' files
    diff = difflib.ndiff(temp_lines, sample_lines)
    if filter(lambda x: not x.startswith('  '), diff):
        print "{0} test failed.".format(fmt.upper())
        return 1

    return 0

if __name__ == '__main__':
    dirname = os.path.dirname(sys.argv[0])
    os.chdir(dirname)

    psdfile = "sample.psd"
    psdfiles = "sample.psd sample.psd"


    print "### Single input file test"
    status = 0
    status += run_test("text", "sample.txt", psdfile)
    status += run_test("xml", "sample.xml", psdfile)
    status += run_test("json", "sample.json", psdfile)

    if status == 0: print "### OK."


    print "### Multiple input files test"
    status = 0
    status += run_test("text", "sample_multi.txt", psdfiles)
    status += run_test("xml", "sample_multi.xml", psdfiles)
    status += run_test("json", "sample_multi.json", psdfiles)

    if status == 0: print "### OK."
