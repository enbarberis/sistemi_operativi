#!/bin/sh

find $HOME \! -user brb -regextype posix-extended -regex ".*\.c"
