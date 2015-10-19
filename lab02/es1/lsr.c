#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>

void lsr(char *path);

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		lsr("./");
	}
	else
	{
		if(argv[1][strlen(argv[1]) - 1] == '/')
		{
			argv[1][strlen(argv[1]) - 1] = '\0';
		}
		lsr(argv[1]);
	}

	return 0;
}

void lsr(char *path)
{
	struct stat stat_buffer;
	DIR *dp;
	struct dirent *dir_entry;
	char file_name[PATH_MAX + 1];
	char full_file_name[PATH_MAX + 1];

	//get info about file
	if(lstat(path, &stat_buffer) < 0)
	{
		fprintf(stderr, "Can't get information about the file %s\n", path);
		exit(-2);
	}

	//check if it's NOT a folder
	if(!S_ISDIR(stat_buffer.st_mode))
	{
		fprintf(stderr, "Can't get the entries of a file!\n");
		exit(-3);
	}

	//if it's a folder, open it
	if((dp = opendir(path)) == NULL)
	{
		fprintf(stderr, "Can't open dir %s\n", path);
		exit(-4);
	}

	printf("\n%s :\n", path);


	//FIRST: print all entries
	while((dir_entry = readdir(dp)) != NULL)
	{
		strncpy(file_name, dir_entry->d_name, PATH_MAX);
		
		if(strcmp(file_name, ".") != 0 && strcmp(file_name, "..") != 0)
		{
			//print entry
			printf("%s\n", file_name);
		}
	}

	//SECOND: get a list of all the directories and go in them
	dp = opendir(path);
	while((dir_entry = readdir(dp)) != NULL)
	{
		strncpy(file_name, dir_entry->d_name, PATH_MAX);
		//if it's not this dir or parent dir
		if(strcmp(file_name, ".") != 0 && strcmp(file_name, "..") != 0)
		{
			//concatenate file name to get full file name
			sprintf(full_file_name, "%s/%s", path, file_name);

			//get stat of the entry
			if(lstat(full_file_name, &stat_buffer) < 0)
			{
				fprintf(stderr, "Can't get information about the file %s\n",
						full_file_name);
				exit(-5);
			}

			//if the entry is a dir
			if(S_ISDIR(stat_buffer.st_mode))
			{
				lsr(full_file_name);
			}
		}
	}
}
