#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

#define VERBOSE 1

void cpr(char *src_path, char *dest_path);

int main(int argc, char **argv)
{
	if(argc < 3)
	{
		fprintf(stderr, "Parameters error!\n"
				"Usage: ./cpr <src-dir> <dest-dir>\n");
		return -1;
	}

	//clean path
	if(argv[1][strlen(argv[1]) - 1] == '/')
	{
		argv[1][strlen(argv[1]) - 1] = '\0';
	}

	if(argv[2][strlen(argv[2]) - 1] == '/')
	{
		argv[2][strlen(argv[2]) - 1] = '\0';
	}

	cpr(argv[1], argv[2]);
	
	return 0;
}

void cpr(char *src_path, char *dest_path)
{
	struct stat stat_buffer;
	DIR *dp;
	struct dirent *dir_entry;
	char file_name[PATH_MAX + 1];
	char full_src_file_name[PATH_MAX + 1];
	char full_dest_file_name[PATH_MAX + 1];
	int fd_in;
	int fd_out;
	char buffer[1024];

	//get info about src_path
	if(lstat(src_path, &stat_buffer) < 0)
	{
		fprintf(stderr, "Can't get information about the src path %s\n", 
				src_path);
		exit(-2);
	}

	//check if src_path it's NOT a folder
	if(!S_ISDIR(stat_buffer.st_mode))
	{
		fprintf(stderr, "Can't copy recursively a file!\n");
		exit(-3);
	}
	
	//create the folder
	if(mkdir(dest_path, S_IRWXU) < 0)
	{
		fprintf(stderr, "Can't create folder %s\n", dest_path);
		exit(-4);
	}
	
	//if it's a folder, open it
	if((dp = opendir(src_path)) == NULL)
	{
		fprintf(stderr, "Can't open dir %s\n", src_path);
		exit(-5);	
	}

	while((dir_entry = readdir(dp)) != NULL)
	{
		strncpy(file_name, dir_entry->d_name, PATH_MAX);
		
		//if it's not this dir or parent dir
		if(strcmp(file_name, ".") != 0 && strcmp(file_name, "..") != 0)
		{
			//concatenate file name to get full file name
			sprintf(full_src_file_name, "%s/%s", src_path, file_name);
			sprintf(full_dest_file_name, "%s/%s", dest_path, file_name);

			//get stat of the entry
			if(lstat(full_src_file_name, &stat_buffer) < 0)
			{
				fprintf(stderr, "Can't get information about the file %s\n",
					full_src_file_name);
					exit(-6);
			}

			//if the entry is a dir
			if(S_ISDIR(stat_buffer.st_mode))
			{
				cpr(full_src_file_name, full_dest_file_name);
			}
			else
			{
				//if it is a file, copy it!
				if(VERBOSE)
				{
					printf("%s -> %s\n", full_src_file_name, full_dest_file_name);
				}

				fd_in = open(full_src_file_name, O_RDONLY);

				if(fd_in < 0)
				{
					fprintf(stderr, "Can't open file %s\n", full_src_file_name);
					exit(-7);
				}

				fd_out = open(full_dest_file_name, O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);

				if(fd_out < 0)
				{
					fprintf(stderr, "Can't create or write file %s\n", full_dest_file_name);
					exit(-8);
				}

				while(read(fd_in, &buffer, 1024) > 0)
				{
					write(fd_out, &buffer, 1024);
				}

				close(fd_in);
				close(fd_out);		
			}
		}
		
	}
}
