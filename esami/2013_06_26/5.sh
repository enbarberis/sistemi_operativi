#!/bin/bash

#controllo parametri
if [ $# -lt 1 ] ; then
	echo "Usage: $0 <dir>"
	exit 1
fi

for f in $(find $1 -type f -name "*.txt")
do
	if egrep --quiet -e "^[0-9]." $f 
	then
		new_name=$(basename $f ".txt")
		new_ext=".mod"
		new_file="$new_name$new_ext"
		echo -n > $new_file

		while read row
		do
			if echo "$row" | egrep --quiet -v -e "^[0-9]."
			then
				echo $row >> $new_file
			fi
		done < $f 
	fi
done
