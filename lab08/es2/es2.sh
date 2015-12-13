#!/bin/bash

if [ $# -lt 1 ]
then
	echo "Parameter error!\nUsage: ./es2 <input file>"
	exit
fi

#var
n=0		#number of rows
maxlen=0	#max str length
strlen=0	#actual string length

while read row
do
	let "n = n + 1"		#n++

	strlen=$(echo "$row" | wc -c) #NON CI VA LO SPAZIO!!!
	
	if [ $strlen -gt $maxlen ]
	then
		maxlen="$strlen"
	fi

done < $1

echo "Longest string: $maxlen char"
echo "Number of rows: $n"
