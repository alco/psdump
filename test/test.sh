#!/bin/bash

cd `dirname $0`

psdump="../build/psdump"
psdfile="sample.psd"

# First compare output to samples with single input file

echo "### Single input file test"
status=0

$psdump $psdfile | diff sample.txt - >/dev/null
if [ "$?" -ne "0" ]; then
    echo "TEXT test failed."
    status=1
fi

$psdump -f xml $psdfile | diff sample.xml - >/dev/null
if [ "$?" -ne "0" ]; then
    echo "XML test failed."
    status=1
fi

$psdump -f json $psdfile | diff sample.json - >/dev/null
if [ "$?" -ne "0" ]; then
    echo "JSON test failed."
    status=1
fi

if [ "$status" -eq "0" ]; then
    echo "### OK."
fi

# Now compare output to sample with multiple input files

echo "### Multiple input files test"

psdfiles="sample.psd sample.psd"

$psdump $psdfiles | diff sample_multi.txt - >/dev/null
if [ "$?" -ne "0" ]; then
    echo "TEXT test failed."
    status=1
fi

$psdump -f xml $psdfiles | diff sample_multi.xml - >/dev/null
if [ "$?" -ne "0" ]; then
    echo "XML test failed."
    status=1
fi

$psdump -f json $psdfiles | diff sample_multi.json - >/dev/null
if [ "$?" -ne "0" ]; then
    echo "JSON test failed."
    status=1
fi

if [ "$status" -eq "0" ]; then
    echo "### OK."
fi
