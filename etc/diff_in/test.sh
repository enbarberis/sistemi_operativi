#!/bin/bash

echo "Metodo 1"

#METODO STANDARD: VAR SEPARATE DA SPAZIO
for var in "var1" "var2" "var3"
do
	echo "$var"
done


echo
echo "Metodo 2"

array=( "var1" "var2" "var3" )
#SE VOGLIO ITERARE ARRAY DEVO FARE COSI`
for var in ${array[*]}
do
	echo "$var"
done

echo
echo "Metodo 3"

#RECUPERA TUTTE LE VARIABILI SEPARATI DA BLANK (non da spazi)
for var in $(cat inp.txt)
do
	echo "$var"
done
