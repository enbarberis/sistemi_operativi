#!/bin/bash

if [ $# -lt 2 ]
then
	echo "Parameters error!"
	echo "Usage: ./es5 <process> <time>"
	exit
fi


flag=0
counter=0

while [ $flag -eq 0 ]
do
	output=$(ps -el | grep $1 | cut -d " " -f 2)
	#echo $output

	if [ -z "$output" ]
	then
		echo "Process stopped"
		exit
	fi

	if [ "$output" = "S" ]
	then
		let "counter++"
	fi

	if [ "$counter" -ge 5 ]
	then
		echo "Sleep process"
		exit
	fi

	sleep $2
done
