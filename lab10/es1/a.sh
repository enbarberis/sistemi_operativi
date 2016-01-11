#!/bin/sh

ps -el | awk '{if($4 == 1) print $14}'
