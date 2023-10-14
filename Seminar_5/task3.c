#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define buffer_size 100

int main()
{
  struct stat st;
  int fd;
  size_t size = 0;
  char buffer_string[buffer_size+1];
    

  if((fd = open("myfile2", O_RDONLY, 0666)) < 0){
    printf("Can\'t open file\n");
    exit(-1);
  }

  size = read(fd, buffer_string, buffer_size);
  
  if(size < 0){
    printf("Can\'t read string\n");
    exit(-1);
  }
  
  printf("%s\n",buffer_string);

  return 0;
}
