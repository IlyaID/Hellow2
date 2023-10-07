#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define buf_size 1000

int main()
{
  struct stat st;
  int fd;
  size_t size;
  char buffer_string[buf_size+1];
  
  (void)umask(0);

  if((fd = open("myfile", O_WRONLY | O_CREAT, 0666)) < 0){
    printf("Can\'t open file\n");
    exit(-1);
  }

  size = read(fd, buffer_string, buf_size);
  if(size < 0){
  /* Если прочитать не смогли, сообщаем об ошибке */
    printf("Can\'t read string\n");
    exit(-1);
  }
  /* Печатаем прочитанную строку */
  printf("%s\n",buffer_string);

  return 0;
}
