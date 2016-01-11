#!/bin/bash

if [ $# -lt 2 ] ; then
	echo "Parameters error!"
	echo "Usage $0 <user> <dir>"
	exit 1
fi

files=$(find $2 -user $1 -type f)

for f in $files
do

	if egrep --quiet "^\*\*\*Da modificare" $f
	then
		awk '{if ($0 !~ /^\*\*\*Da modificare/) print $0;}' $f > tmp
		mv tmp $f"_mod"
		#rm -f $f
	fi
done
