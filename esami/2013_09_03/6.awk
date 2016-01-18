#!/usr/bin/awk -f
BEGIN{
	n = 0;
	somma = 0;
}


{
	for(i=1; i<=NF; i++)
	{
		if($i ~ /^[0-9]+$/)
		{
			print $i;
			
			if(n == 0)
			{
				max = $i;
				min = $i;
			}
			else
			{
				somma += $i;
				if($i < min)
					min = $i;
				if($i > max)
					max = $i;
			}

			n++;
		}
	}
}

END{
	if(n > 0)
	{
		printf("\nLa media dei numeri e`: %d\n", somma/n);
		printf("minimo: %d\nmassimo: %d\n", min, max);
	}
}
