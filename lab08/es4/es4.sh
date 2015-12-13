#/bin/bash

if [ $# -lt 1 ]
then
	#read text from stdin
	read text
else
	#read text from file
	text=$(cat $1)
fi

n=0		#number of different words
words=""	#array of different words
occur=0		#array of word occurrences

for word in $text
do
	#search if $word is already in the array $words
	i=0
	while [ $i -lt $n ]
	do
		if [ "$word" = "${words[$i]}" ]
		then
			let "occur[i] += 1"
			break
		fi

		let "i += 1"
	done

	#if there isn't add it
	if [ $i -eq $n ]
	then
		words[$n]="$word"
		occur[$n]=1
		let "n += 1"
	fi
done

i=0
while [ $i -lt $n ]
do
	echo "${words[$i]} ${occur[$i]}"
	let "i++"
done
