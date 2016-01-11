#!/bin/sh

if [ $# -lt 1 ]
then
	echo "Parameters error!\nUsage: ./es2 <PID>"
else
	ps -el | awk -v pid=$1 -f stampa.awk
fi
