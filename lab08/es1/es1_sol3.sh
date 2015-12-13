#!/bin/sh

#Check and save parameters
if [ $# -lt 3 ] ; then
	echo "Parameters error!\nUsage: ./es1.sh <dir> <function> <out_file>"
	exit;
fi

rm -f $output_file

directory=$1
function=$2
output_file=$3

#recive a list of all files
all_files=$(find $directory -type f)

#for every file in directory
for f in $all_files
do	
	#search function and print to output_files
	egrep -HIn ".*$function\(.*\).*" $f >> $output_file
done

#sort by name and line count
sort -o $output_file -t ":" -k 1,2 $output_file
