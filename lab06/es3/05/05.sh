#!/bin/sh

find $HOME -regextype posix-extended -regex ".*/A.*zzz.*\..{3}" -exec gzip \{} -k \;
