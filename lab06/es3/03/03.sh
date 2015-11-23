#!/bin/sh
find /home/brb/sistemi_operativi -regextype posix-extended -regex "(.*a.*A.*)|(.*A.*a.*)" -user brb -type f -exec tail -n 3 \{} \;
