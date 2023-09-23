//Задание 4

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    for(int i = 0; i < argc; i++){
        printf("Argc%d = %s\n", i, argv[i]);
    }

    int i = 0;
    while(envp[i] != NULL){
        printf("envp%d = %s\n", i, envp[i]);
        i++;
    }

    if(argc == 1) {
        printf("Command line has no additional arguments\n");
    }
    return 0;

}