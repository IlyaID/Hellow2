#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int     fd[2], result;

   size_t size;
   char  resstring[14];

   if(pipe(fd) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }

   result = fork();

   if(result < 0) {
      printf("Can\'t fork child\n");
      exit(-1);
   } 
   else if (result > 0) {

     /* Parent process */

      close(fd[0]);
      printf("Hello, child!\n");
      size = write(fd[1], "Wash the dish", 14);

      if(size != 14){
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }

      close(fd[1]);
      printf("I send you messege\n Good day, daughter!\n");

   } 
   else {

      /* Child process */

      close(fd[1]);
      size = read(fd[0], resstring, 14);

      if(size < 0){
         printf("Can\'t read string from pipe\n");
         exit(-1);
      }

      printf("I get your massege:%s\n", resstring);
      printf("Bye, mother!\n");
      close(fd[0]);
   }

   return 0;
}
