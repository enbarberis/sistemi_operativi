#!/usr/bin/awk -f

BEGIN{

	if(ARGC < 3)
	{
		printf("Parameters error!\nUsage: %s <inp_file> <out_file>\n", ARGV[0]);
		exit 1
	}

	while((getline < ARGV[1]))
	{
		split($3, partenza, ":");
		split($4, arrivo, ":");

		printf("'%s' %d\n\n", partenza[2], length(partenza[2]));

		if(length(partenza[1]) < 2)
			partenza[1] = "0" partenza[1];
		if(length(paretenza[2]) < 2)
			partenza[2] = "0" partenza[2];
	
		if(length(arrivo[1]) < 2)
			arrivo[1] = "0" arrivo[1];
		if(length(arrivo[2]) < 2)
			arrivo[2] = "0" arrivo[2];


	
		printf("%s %s %s:%s %s:%s\n", $1, $2, partenza[1], partenza[2], arrivo[1], arrivo[2]) > ARGV[2];
	}
}
