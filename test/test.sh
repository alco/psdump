#!/bin/bash

cd `dirname $0`

psdump="../build/psdump -o temp"
psdfile="sample.psd"

# First compare output to samples with single input file

echo -n "### Single input file test..."
status=0

text_result=`$psdump $psdfile`
diff temp sample.txt
if [ "$?" -ne "0" ]; then
    echo "TEXT test failed."
    status="bad"
fi

xml_result=`$psdump -f xml $psdfile`
diff temp sample.xml
if [ "$?" -ne "0" ]; then
    echo "XML test failed."
    status="bad"
fi

json_result=`$psdump -f json $psdfile`
diff temp sample.json
if [ "$?" -ne "0" ]; then
    echo "JSON test failed."
    status="bad"
fi

if [ "$status" -eq "0" ]; then
    echo "OK."
fi

# Now compare output to sample with multiple input files

echo -n "### Multiple input files test..."

psdfiles="sample.psd sample.psd"

text_result=`$psdump $psdfiles`
diff temp sample_multi.txt
if [ "$?" -ne "0" ]; then
    echo "TEXT test failed."
    status="bad"
fi

xml_result=`$psdump -f xml $psdfiles`
diff temp sample_multi.xml
if [ "$?" -ne "0" ]; then
    echo "XML test failed."
    status="bad"
fi

json_result=`$psdump -f json $psdfiles`
diff temp sample_multi.json
if [ "$?" -ne "0" ]; then
    echo "JSON test failed."
    status="bad"
fi

if [ "$status" -eq "0" ]; then
    echo "OK."
fi