#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int num;

	do
	{
		scanf("%d", &num);
		
		if(num != 0)
		{
			if(num % 2 == 0)	
			{
				fprintf(stdout, "%d\n", num);
			}
			else
			{
				fprintf(stderr, "%d\n", num);
			}
		}

	}while(num != 0);

	return 0;
}
