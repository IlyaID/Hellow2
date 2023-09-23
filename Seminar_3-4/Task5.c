//Задание 5

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{

    (void) execle("/bin/cat", "/bin/cat", "Task8.c", 0, envp);

    printf("Error on program start\n");
    exit(-1);

    return 0;
}

