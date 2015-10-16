#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int  main()
{
	int pid;

	pid = fork();

	if(pid == -1)
	{
		fprintf(stderr, "Can't create process\n");
	}
	else if(pid == 0)
	{
		//child process code
		printf("I'm child process and my pid is %d\n", getpid());
		fflush(stdout);

		int stat_val;
		int pid_child = wait(&stat_val);

		printf("Ok, my child %d as ended and it's exited ", pid_child);
			
		if (WIFEXITED(stat_val))
		{
			printf("Valore restituito: %d\n", WEXITSTATUS (statVal));
		}
		else
		{
			printf("Terminazione anormale\n");
		}
	}


	}
	else
	{
		//father process code
		printf("I'm father process and my pid is %d\n", getpid());
		fflush(stdout);

		sleep(10);

		return 4;
	}
	
	return 0;
}

