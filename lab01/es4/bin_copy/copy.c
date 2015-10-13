#include <stdio.h>
#include <sys/stat.h>                                                    
#include <fcntl.h>                                                     
#include <unistd.h>

int main(int argc, char **argv)
{
	int fd_in;
	int fd_out;
	char buffer;
	
	if(argc < 3)
  	{
   		fprintf(stderr, "Parameters error!\nUsage: ./copy <src> <dest>\n");
    		return -1;
	}
	
	fd_in = open(argv[1], O_RDONLY);

	if(fd_in < 0)
	{
		fprintf(stderr, "Can't open file %s\n", argv[1]);
		return -2;
	}

	fd_out = open(argv[2], O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);

	if(fd_out < 0)
	{
		fprintf(stderr, "Can't create or write file %s\n", argv[2]);
		return -3;
	}

	while(read(fd_in, &buffer, 1) > 0)
	{
		write(fd_out, &buffer, 1);
	}

	close(fd_in);
	close(fd_out);

	return 0;
}
