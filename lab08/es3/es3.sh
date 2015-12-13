#!/bin/bash

if [ $# -lt 1 ]
then
	echo "Parameters error!\nUsage: ./es3 <dir>"
	exit
fi

for f in $(ls $1)
do
	upper_case=$(echo "$f" | tr '[:lower:]' '[:upper:]')
	mv "$1/$f" "$1/$upper_case"
done

