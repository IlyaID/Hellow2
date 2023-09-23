//Задание 6

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    
    (void) execv("../task4", "12 12 12 10");
    printf("Error on program start\n");
    exit(-1);
 
    
    return 0;

}
    