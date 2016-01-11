#!/usr/bin/awk -f

BEGIN{
	cmd = "ps -el";
	
	while(cmd | getline > 0)
	{
		if($2 == "R" || $2 == "R+") print $4 " - " $14
	}

	close(cmd);
}
