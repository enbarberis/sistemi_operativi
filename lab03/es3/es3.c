#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_error(const char *msg, int exit_value);

int main(int argc, char **argv)
{
    int pid;

    pid = fork();
    if(pid < 0)
    {
        print_error("Can't fork #1", -1);
    }
        
    return 0;
}


void print_error(const char *msg, int exit_value)
{
    fprintf(stderr, "%s\n", msg);
    exit(exit_value);
}


