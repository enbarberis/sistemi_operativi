#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BIN_FILE "bin.dat"
#define OUT_FILE "output.txt"

int txt_to_bin(char *txt_file, char *bin_file);
void bubble_sort_swap(int fd, int pos);

int main(int argc, char **argv)
{
	int n;		//number of numbers
	int i,j;	//iterators
	int pid;	//fork pid
	int fd;		//bin file file descriptor
	FILE *fp;	//file pointer of output file
	int num;	//var to store readed numbers from bin file during the output

	if(argc < 2)
	{
		fprintf(stderr, "Parameters error!\nUsage: ./es2 <inp_file>\n");
		return 1;
	}

	n = txt_to_bin(argv[1], BIN_FILE);

	fd = open(BIN_FILE, O_RDWR);
	if(fd < 0)
	{
		fprintf(stderr, "Can't open file %s\n", BIN_FILE);
		return 2;
	}

	for(i=0; i<n-1; i++)
	{
		//extern loop
		for(j=n-i-2; j>0; j--)
		{
			//inside loop
			pid = fork();
			if(pid < 0)
			{
				fprintf(stderr, "Can't fork!\n");
				return 1;
			}
			else if(pid > 0)
			{
				//father waits child
				waitpid(pid, (int *)0, 0);
				break;
			}
		}

		//codice scambio che child esegue
		bubble_sort_swap(fd, j);

		//only first father must survive
		if(j  < n-i-2)		
		{
			exit(0);
		}
	}

	//print sorted file in output.txt
	if((fp = fopen(OUT_FILE, "w")) == NULL)
	{
		fprintf(stderr, "Can't create file %s\n", OUT_FILE);
		exit(4);
	}

	lseek(fd, 0, SEEK_SET);

	while(read(fd, &num, sizeof(int)) > 0)
	{
		fprintf(fp, "%d\n", num);
	}

	close(fd);
	fclose(fp);

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

void bubble_sort_swap(int fd, int pos)
{
	int num_1;
	int num_2;

	lseek(fd, sizeof(int)*pos, SEEK_SET);
	
	if(!read(fd, &num_1, sizeof(int)))
	{
		fprintf(stderr, "Can't read\n");
		exit(3);
	}
	
	if(!read(fd, &num_2, sizeof(int)))
	{
		fprintf(stderr, "Can't read\n");
		exit(3);
	}

	//if bigger number is on the left do the swap
	if(num_1 > num_2)
	{
		//printf("SWYPE\n");
		lseek(fd, sizeof(int)*pos, SEEK_SET);
		write(fd, &num_2, sizeof(int));
		write(fd, &num_1, sizeof(int));
	}
}
