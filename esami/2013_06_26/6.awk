#!/usr/bin/awk -f

BEGIN{
	if(ARGC < 3)
	{
		printf("Param. error\nUsage: %s <fil1> <file2>\n", ARGV[0]);
		exit(1);
	}
}

{
	if (!($1 in tempo_tot))
	{
		tempo1[$1] = $2;
		tempo2[$1] = $3;
		tempo3[$1] = $4;
		tempo_tot[$1] = $2 + $3 + $4;
		stringa[$1] = "ONE";
	}
	else
	{
		stringa[$1] = "BEST";

		if(tempo_tot[$1] > $2 + $3 + $4)
		{
			tempo1[$1] = $2;
			tempo2[$1] = $3;
			tempo3[$1] = $4;
			tempo_tot[$1] = $2 + $3 + $4;
		}
	}
}

END{

	for (i in tempo_tot)
	{
		printf("%s\t%f\t%f\t%f\t%f\t%s\n", i, tempo1[i], tempo2[i], tempo3[i], tempo_tot[i], stringa[i]);
	}

}
