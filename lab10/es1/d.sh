#!/bin/sh

ps -el | awk '{if($2 == "R" || $2 == "R+") print $14 " - " $4 }' | sort
