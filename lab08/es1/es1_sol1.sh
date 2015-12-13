#!/bin/sh

#Check and save parameters
if [ $# -lt 3 ] ; then
	echo "Parameters error!\nUsage: ./es1.sh <dir> <function> <out_file>"
	exit;
fi

directory=$1
function=$2
output_file=$3

#Searching
find $directory -type f -exec egrep -HnI ".*$function\(.*\).*" \{} \; > $output_file

#Sorting
sort -o $output_file -t ":" -k 1,2 $output_file  
