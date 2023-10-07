#include <stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

 
int main(int argc, char* argv[])
{
    int fd[2];
    size_t size = 0;
    char resstring[15]={"Hellow, mother!\n"};
 
    fd[0] = atoi(argv[1]);
    fd[1] = atoi(argv[2]);
 
    close(fd[0]);
    
    size = write(fd[1], resstring, 15);
  
    if (size != 15) {
        printf("Can\'t read string\n");
        exit(-1);
    }
      
    close(fd[1]);
    return 0;
}