#include <stdio.h>
#include <stdio.h>
#define DIM 256

int main(int argc, char **argv)
{
	FILE *fp_in;
	FILE *fp_out;
	char buffer[DIM + 1];

	if(argc < 3)
	{
		fprintf(stderr, "Parameters error!\nUsage: ./copy <src> <dest>\n");
		return -1;
	}

	if((fp_in = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Can't open file %s\n", argv[1]);
		return -2;
	}

	if((fp_out = fopen(argv[2], "w")) == NULL)
	{
		fprintf(stderr, "Can't create file %s\n", argv[2]);
		return -3;
	}

	while(fgets(buffer, DIM, fp_in) != NULL)
	{
		fputs(buffer, fp_out);
	}

	fclose(fp_in);
	fclose(fp_out);

	return 0;
}
