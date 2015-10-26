#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int i;

	for(i=3; i>1; i--) 
	{
		sleep(1);
		if (fork ())
			printf ("%d\n", i);
	}
	printf ("%d\n", i);


	return 0;
}


