#!/bin/sh

find /usr/lib -type d -regextype posix-extended -regex ".*/bin" -exec echo \{} \; -exec ls \{} \;
