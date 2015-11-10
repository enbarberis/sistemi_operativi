#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BIN_FILE "bin.dat"

int txt_to_bin(char *txt_file, char *bin_file);

int main(int argc, char **argv)
{
	int n;		//number of numbers
	
	if(argc < 2)
	{
		fprintf(stderr, "Parameters error!\nUsage: ./es2 <inp_file>\n");
		return 1;
	}

	n = txt_to_bin(argv[1], BIN_FILE);

	

	return 0;
}

int txt_to_bin(char *txt_file, char *bin_file)
{
	FILE *fp;
	int i, n, x;
	int fd;

	if((fp = fopen(txt_file, "r")) == NULL)
	{
		fprintf(stderr, "Can't open file %s\n", txt_file);
		exit(1);
	}

	fd = open(bin_file, O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	if(fd < 0)
	{
		fprintf(stderr, "Can't create file %s\n", bin_file);
		exit(1);
	}

	fscanf(fp, "%d", &n);

	for(i=0; i<n; i++)
	{
		fscanf(fp, "%d", &x);
		write(fd, &x, sizeof(x));	
	}

	fclose(fp);
	close(fd);

	return n;
}
