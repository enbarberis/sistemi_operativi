#!/bin/sh

#1
sort elenco.txt -nr > 1.txt

#2
sort elenco.txt -k 2 > 2.txt

#3 
grep "2011/2012" elenco.txt > 3.txt

#4
grep "INF1T3" elenco.txt | sort -n > 4.txt

#5
cut -d " " -f 1,4 elenco.txt | egrep -e "(2\>)|(4\>)" | sort -k 2 > 5.txt

#6
egrep -e ".*TLC1T3.*frequentare" elenco.txt| sort -nr > 6.txt

#7
egrep -e ".*A[a-zA-Z]{2}A.*" elenco.txt > 7.txt

#8
egrep -e ".*[a-zA-Z]+A[a-zA-Z]{2}A[a-zA-Z]+.*" elenco.txt > 8.txt

#9
cut -d " " -f 1 elenco.txt | tr -d 0 | tr 8 1 | sort -n | uniq > 9.txt

#9bis
cut -d " " -f 1 test.txt | tr -d 0 | tr 8 1 | sort -n | uniq -d > 9bis.txt
cat 9bis.txt
wc -l 9bis.txt

