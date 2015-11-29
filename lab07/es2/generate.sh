#!/bin/sh

echo $2 > $1
echo >> $1
shuf -i 0-10000 -n $2 >> $1
