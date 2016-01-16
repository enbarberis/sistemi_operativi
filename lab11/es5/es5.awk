#!/usr/bin/awk -f

BEGIN{

	if(ARGC < 3)
	{
		printf("Parameters error!\nUsage: %s <inp_file> <out_file>\n", ARGV[0]);
		exit 1
	}

	out_file = ARGV[2];

	while((getline < ARGV[1]))
	{
		printf("%s %s ", $1, $2) > out_file;

		split($3, partenza, ":");
		split($4, arrivo, ":");


		if(length(partenza[1]) < 2)
			printf("0") > out_file;
		printf("%s:", partenza[1]) > out_file;

		if(length(paretenza[2]) < 2)
			printf("0") > out_file;
		printf("%s ", partenza[2]) > out_file;
	
		if(length(arrivo[1]) < 2)
			printf("0") > out_file;
		printf("%s:", arrivo[1]) > out_file;

		if(length(arrivo[2]) < 2)
			printf("0") > out_file;
		printf("%s\n", arrivo[2]) > out_file;
	}
}
