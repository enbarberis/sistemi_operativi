#!/bin/sh

if [ $# -eq 3 ]
then
	cal $2 $3 | awk -v day=$1 -f es3.awk
else
	echo "Parameters error!\nUsage $0 <gg> <mm> <aaaa>"
fi
