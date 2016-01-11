#!/usr/bin/awk

BEGIN{
	i=0		#line counter
	days=""		#days of the week (mon. tue. ....)
}

{
	#find the correct row where is the day
	i++;

	if(i == 2)
	{
		days = $0;
		split(days, vet);
	}

	if(match($0 , day ))
	{
		for(j=1; j<= NF; j++)
		{
			if($j == day) print vet[j]
		}
	}
}
