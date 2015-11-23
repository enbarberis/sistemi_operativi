#!/bin/sh

#1
sort elenco.txt -nr > 1.txt

#2
sort elenco.txt -k 2 > 2.txt

#3 
grep "2011/2012" elenco.txt > 3.txt

#4
grep "INF1T3" elenco.txt | sort -n > 4.txt

#5 PROBLEMA
grep -e "^(2\>)" elenco.txt | sort -k 2 > 5.txt

#6
egrep -e ".*TLC1T3.*frequentare" elenco.txt| sort -nr > 6.txt

#7 PROBLEMA
egrep -e ".*A.{2}A.*" elenco.txt > 7.txt

#8 PROBLEMA

#9
cut -d " " -f 1 elenco.txt | tr -d 0 | tr 8 1 | sort -n | uniq > 9.txt

#9bis PROBLEMA
cut -d " " -f 1 test.txt | tr -d 0 | tr 8 1 | sort -n | uniq -d > 9bis.txt | wc -l

