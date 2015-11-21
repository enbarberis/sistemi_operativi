#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include <sys/wait.h>

#define PID_FILE_CHILD_1 "pid_child_1.txt"
#define PID_FILE_CHILD_2 "pid_child_2.txt"
#define MAX_STR 256
#define END_STR "end"
#define END_STR_UPP "END"

void to_upper(char *str);

int main(int argc, char **argv)
{
	int pid;
	int pipe_fd[2];

	//reset pid files and char file
	fopen(PID_FILE_CHILD_1, "w");
	fopen(PID_FILE_CHILD_2, "w");

	//pipe creation
	if(pipe(pipe_fd))
	{
		fprintf(stderr, "Can't create pipe!\n");
		return 1;
	}

	pid = fork();

	if(pid < 0)
	{
		fprintf(stderr, "Can't fork!\n");
		return 1;
	}
	else if(!pid)
	{
		//==== CHILD 1 ====
		char str[MAX_STR];
		int len;

		//make pipe simplex
		close(pipe_fd[0]);
		
		do{
			//write(pipe_fd[1], "Ciao", 5);
			scanf("%s", str);
		
			//send str length
			len = strlen(str);
			write(pipe_fd[1], (char *) &len, sizeof(int));

			//send string
			write(pipe_fd[1], str, len+1);
		
		}while(strcmp(str, END_STR) != 0);
	}
	else
	{
		pid = fork();
		if(pid < 0)
		{
			fprintf(stderr, "Can't fork!\n");
			return 2;
		}
		else if(!pid)
		{
			//==== CHILD 2 ====
			char str[MAX_STR];
			int len;

			//make pipe simplex
			close(pipe_fd[1]);
			
			do{
				//read str length and then string
				read(pipe_fd[0], &len, sizeof(int));
				read(pipe_fd[0], str, len+1);

				to_upper(str);

				printf("%s\n", str);

			}while(strcmp(str, END_STR_UPP) != 0);
		}
		else
		{
			//father wait child 2
			waitpid(pid, (int *)0, 0);
		}

		//father wait child 1
		waitpid(pid, (int *)0, 0);
	}

	return 0;
}

void to_upper(char *str)
{
	while(*str != '\0')
	{
		if(islower(*str))
		{
			*str = toupper(*str);
		}

		str++;
	}
}
