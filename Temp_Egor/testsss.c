#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    while(1)
    {
        char str[50];
        char *argv[50];
        scanf("%s", str);
  
        if(strcmp(str, "quit") == 0)
        {
            return 0;
        }
        char *token = strtok(str, " ");
        int j = 0;

        while(token != NULL)
        {
            argv[j++] = token;
            token = strtok(NULL, " ");
        }
        pid_t pid = fork();
        if(pid==0)
        {
            if(execvp(*argv, argv)<0)
            {
                printf("Failed");
                return 0;
            }
        }else if(pid > 0)
        {
            wait(NULL);
            printf("\n");
        }
    }
  
  return 0;
}