#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    for(int i = 0; i <= sizeof argv; i++){
        printf("Argv%d = %c, envp = %c\n", i, argv[i], envp[0]);
    }
    return 0;

}