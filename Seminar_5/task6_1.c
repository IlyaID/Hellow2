#include <stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
 
int main( int argc, char *argv[])
{
    int fd[2], result;
    char fd_0[8], fd_1[8];
    char resstring[15];
    ssize_t size;

    if (pipe(fd) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    result = fork();

    if (result < 0) {
        printf("Can't fork child\n");
        exit(-1);
    }

    if (result == 0) {
            printf("Hellow, I am daughter!\n");
            
            snprintf(fd_0, sizeof(fd_0), "%d", fd[0]);
            //printf("%s\n\n",fd_0);
            //printf("%d\n\n",fd[0]);

            snprintf(fd_1, sizeof(fd_1), "%d", fd[1]);
            //printf("%s\n\n",fd_1);
            //printf("%d\n\n",fd[1]);
            printf("I send message\n");

            execl("./task6_2", "task6_2", fd_0, fd_1, NULL);
            
    }
      
    if (result > 0) {
        close(fd[1]);
        printf("Hellow, I am Perent!\n");
        size = read(fd[0],resstring,15);
        if (size != 15) {
            printf("Can\'t read string\n");
            exit(-1);
        }
        close(fd[0]);

        printf("I am Perent and I get message: %s\n", resstring);
    }

    return 0;
}