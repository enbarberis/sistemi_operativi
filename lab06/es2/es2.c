#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OK 'K'
#define EXIT 'X'

int main(int argc, char **argv)
{
	int pid;
	int pipe_fd_1[2];
	int pipe_fd_2[2];

	//pipe creation
	if(pipe(pipe_fd_1) || pipe(pipe_fd_2))
	{
		fprintf(stderr, "Can't create pipe!\n");
		return 1;
	}

	pid = fork();

	if(pid < 0)
	{
		fprintf(stderr, "Can't fork!\n");
		return 2;
	}
	else if(!pid)
	{
		//CHILD
		char response;

		close(pipe_fd_1[0]);
		close(pipe_fd_2[1]);

		while(1)
		{
			//wait father
			read(pipe_fd_2[0], &response, 1);

			if(response == EXIT)
				break;

			printf("I'm the child (PID=%d)\n", getpid());
			
			//tell father to continue
			response = OK;
			write(pipe_fd_1[1], &response, 1);
		}
	}
	else
	{
		//FATHER
		int i;
		char response;

		close(pipe_fd_2[0]);
		close(pipe_fd_1[1]);

		for(i=0; i<10; i++)
		{
			printf("I'm the father (PID=%d)\n", getpid());

			//tell child that father as printed
			response = OK;
			write(pipe_fd_2[1], &response, 1);

			//wait child
			read(pipe_fd_1[0], &response, 1);
		}

		response = EXIT;
		write(pipe_fd_2[1], &response, 1);
	}

	return 0;
}
