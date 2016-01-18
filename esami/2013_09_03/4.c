#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	int i, n;
	sscanf(argv[1], "%d", &n);
	
	printf("Running process %d with n=%d\n", getpid(), n);

	for(i=0; i<n; i++)
	{
		if(fork())
		{
			//i padri muoiono senza aspettare i figli
			exit(0);
		}
		else
		{
			if(i % 2 != 0)
			{
				//figli dispari
				char msg[256];
				sprintf(msg, "echo 'Figlio dispari %d con PID=%d'", i, getpid());
				system(msg);
			}
			else
			{
				//figli pari
				printf("Figlio pari %d con PID=%d\n", i, getpid());
				char param[256];
				sprintf(param, "%d", n-1);

				execlp(argv[0], argv[0], param, NULL);
			}
		}
	}

}
