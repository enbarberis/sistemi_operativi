#include <stdio.h>
#include <sys/stat.h>                                                        
#include <fcntl.h>                                                     
#include <unistd.h>

int main(int argc, char **argv)
{
  char buffer;
  int fd;
  
  if(argc < 2)
  {
    write(STDOUT_FILENO, "parameters error\n", 17);
    return -1;
  }

  fd = open(argv[1], O_RDONLY);

  if(fd == -1)
  {
    write(STDOUT_FILENO, "can't open file\n", 16);
    return -2;
  }

  while(read(fd, &buffer, 1) > 0)                                              
  {
    printf("%c\t%03d\t%02x\n", buffer, buffer, buffer);
  }

  close(fd);

  return 0;
}
