#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
   int     fd;
   size_t  size;
   char    string[] = "Hello, world!";

   (void)umask(0);
   
   if(fd = open("myfile", O_WRONLY | O_CREAT, 0666)<0){
     printf("Can\'t open file\n");
     exit(-1);
   }



    
   //size = write(fd, string, 14);
/*
   if(size != 14){
     printf("Can\'t write all string\n");
     exit(-1);
   }
*/
   if(close(fd) < 0){
     printf("Can\'t close file\n");
   }
    int N  = 20;
    char str[N];
    read(fd,str,14);

   return 0;
}