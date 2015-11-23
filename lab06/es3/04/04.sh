#!/bin/sh
echo "BYTE"
find $HOME -mindepth 3 -maxdepth 5 -user brb -size +250b -regextype posix-extended -regex ".*/.{4}" -exec wc -c \{} \;

echo "LINES"
find $HOME -mindepth 3 -maxdepth 5 -user brb -size +250b -regextype posix-extended -regex ".*/.{4}" -exec wc -l \{} \;
