# -*- coding: utf-8 -*-

import os
import sys
import filecmp
import tempfile
from subprocess import call

def run_test(fmt, sample, arg):
    temp = tempfile.NamedTemporaryFile()
    psdump = "../build/psdump -o {0} -f {1} {2}".format(temp.name, fmt, arg)

    call(psdump.split())
    if not filecmp.cmp(temp.name, sample):
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
