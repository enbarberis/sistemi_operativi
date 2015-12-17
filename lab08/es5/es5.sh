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
	echo "Status: $output"

	if [ -z "$output" ]
	then
		echo "Process stopped"
		exit
	fi

	#if [ "$output" = "Z" ]
	#then
	#	let "counter++"
	#fi

    for stat in $output
    do
        if [ $stat = "Z" ]
        then
            let "counter++"
            echo "ci sta zombie"
        fi
    done

	if [ "$counter" -ge 5 ]
	then
		echo "Zombie process for 5 times"
		exit
	fi

	sleep $2
done
