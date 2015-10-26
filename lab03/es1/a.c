#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int i;

	for (i=1; i<=2; i++) 
	{
		if (!fork ())
		{
			//sleep(5);
			printf("%d > %d\n", getpid(), i);
		}
	}
 
	printf ("%d > %d\n", getpid(), i);

	return 0;
}


