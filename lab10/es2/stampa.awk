#!/usr/bin/awk -f
$4 == pid { print $14 " - " $4 }

