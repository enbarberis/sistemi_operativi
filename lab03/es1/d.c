#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int i;

	for (i=2; i>=1; i--) 
	{
		if (!fork ())
			printf ("%d\n", -i);
	    	else
		        printf ("%d\n", i);
	}

	return 0;
}


