#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


int main()
{
  struct stat st;
  int fd;
  size_t size;
  size_t bytes_read;
  char buffer_string[1000];
  
  (void)umask(0);

  if((fd = open("myfile", O_WRONLY | O_CREAT, 0666)) < 0){
    printf("Can\'t open file\n");
    exit(-1);
  }

  /*
  fstat(fd, &st);
  size = st.st_size;
  */

  size = 14;
  printf("%d\n",size);

  if(size >= 1000){
    printf("Can\'t write all string\n");
    exit(-1);
    }

  /*
  if ((bytes_read = read(fd, buffer_string, size)) < 0){
    printf ("Possible read error.\n");
    exit(-1);
  }
*/
  for (int i = 0; i <= size; i++){
    if (read(fd, buffer_string + i, 1) < 0){
        printf ("Possible read error.\n");
        exit(-1);
    }
  }


  for (int i = 0; i <= size; i++){
    printf("%c",buffer_string[i]);
  }
    printf("\n");
   /*
  char ch;
  while ((bytes_read = read (fd, &ch, 1)) > 0){
		putchar (ch);
  }
*/ 
  if(close(fd) < 0){
    printf("Can\'t close file\n");
    exit(-1);
  }

  return 0;
}
