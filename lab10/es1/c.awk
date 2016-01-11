#!/usr/bin/awk -f

BEGIN{
	cmd = "ps -el";

	while(cmd | getline > 0)
	{
		if($2 == "R" || $2 == "R+") output = output $14 " - " $4 "\n"
	}

	close(cmd);

	print output | "sort"
}
