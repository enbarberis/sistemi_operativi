#!/bin/bash

function print_help
{
	echo "Usage: $0 <options> <dictionary> <inp_file> <out_file>"
	echo
	echo "OPTIONS"
	echo "-h | --help : print program help"
	echo
	echo "-l | --longest : choose longest translation (default option)"
	echo
	echo "-s | --shortest : choose shortest translation"
	echo
	echo "-num <num> : chose always #num transalation from dictionary"
	echo
	echo "-v | --verbose : show warnings"

}

#VAR
dictionary=""		#dictionary file
inp_file=""		#input file
out_file=""		#output file
longest=0
shortest=0
verbose=0
num_search=-1
end_options=0		#become true when options parse has ended
next=0			#var to distinguish dict, inp_file, out_file
next_is_n=0		#var to read parameter n after the current loop
ok=0			#equals to 1 if alla parameters are correct

#parameters control
for param in $*
do
	if [ $next_is_n -eq 1 ] || echo $param | grep -q "-" 	
	then
		#It's an option
		if [ $param == "-h" -o $param == "--help" ] ; then
			print_help
			exit 0
		fi
		
		if [ $param == "-l" -o $param == "--longest" ] ; then
			longest=1
		fi

		if [ $param == "-s" -o $param == "--shortest" ] ; then
			shortest=1
		fi

		if [ $param == "-v" -o $param == "--verbose" ] ; then
			verbose=1
		fi

		if [ $next_is_n -eq 1 ] ; then
			num_search=$param
			next_is_n=2
		fi

		if [ $param == "-num" ] ; then
			next_is_n=1
		fi

	else
		#Options has ended
		if [ $next -eq 2 ] ; then
			out_file=$param
			next=3
		fi

		if [ $next -eq 1 ] ; then
			inp_file=$param
			next=2
		fi
	
		if [ $next -eq 0 ] ; then
			dictionary=$param
			next=1
		fi
	fi
done

#if there are all minum parameters
if [ $next -eq 3 ] && [ $next_is_n -eq 0 -o $next_is_n -eq 2 ] ; then

	#search conflicts
	if [ $next_is_n -eq 0 ] ; then
		#no num parameters
		let "sum = $longest + $shortest"
		if [ $sum -gt 1 ] ; then
			echo "ERROR:  only one option among -l, -s and -n can be specified"
			exit 1
		fi

		if [ $longest -eq 0 -a $shortest -eq 0 ] ; then
			longest=1
		fi
	else
		let "sum = $longest + $shortest + 1"
		if [ $sum -gt 1 ] ; then
		echo "ERROR:  only one option among -l, -s and -n can be specified"
		exit 1
		fi
	fi

	#control if num is a number
	if ! let "$num_search + 0" ; then 
		echo "ERROR! num. translation isn't a number!"
		exit 1
	fi

	#everything is ok! Call awk script

	awk -v longest=$longest -v shortest=$shortest -v num_search=$num_search -v verbose=$verbose -v dictionary="$dictionary" -v inp_file="$inp_file" -f translate.awk 

#> $out_file

fi
	
#	echo "Parameters OK!"
#	echo "dictionary: $dictionary"
#	echo "inp: $inp_file"
#	echo "out: $out_file"
#	echo "l: $longest"
#	echo "s: $shortest"
#	echo "v: $verbose"
#	echo "num: $num_search"

