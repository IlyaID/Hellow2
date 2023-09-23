//Задание 6
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid, ppid, chpid;
    int a = 0;

    pid = fork();
    if(pid == -1){

        /* ошибка */
    } 
    else if (pid == 0){
        pid  = getpid();
        ppid = getppid();
        a = a+1;
        printf("Hello mother! My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a);
        
        (void) execle("./task4", "task4", "task4","12", "12", "12", "10", NULL, envp);
        printf("Error on program start\n");
        exit(-1);
 
    } else {
        pid  = getpid();
        ppid = getppid();
        a = a+1;
        printf("Hello daughter! My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a);

    }
    return 0;

}
    