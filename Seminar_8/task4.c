#include <sys/types.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n = 3;
    int semid;
    char pathname[] = "task4.c";
    key_t key;
    struct sembuf mybuf;

    key = ftok(pathname, 0);

    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t create semaphore set\n");
        exit(-1);
    }

    int pipe_0[2];
    int result;

    size_t size;
    char resstring[128];

    if (pipe(pipe_0) < 0)
    {
        printf("Can\'t open pipe 1\n");
        exit(-1);
    }

    result = fork();

    if (result < 0)
    {
        printf("Can\'t fork child\n");
        exit(-1);
    }
    else if (result > 0)
    {
        /* Parent process */
        char *messages[3] = {"Hello, C!", "How are you, C?", "Me too"};

        for (int i = 0; i < n; i++)
        {
            size = write(pipe_0[1], messages[i], strlen(messages[i]));

            if (size != strlen(messages[i]))
            {
                printf("Can\'t write all string to pipe from parent to child\n");
                exit(-1);
            }

            printf("Parent sent message: %s\n", messages[i]);

            mybuf.sem_num = 0;
            mybuf.sem_op = 1;
            mybuf.sem_flg = 0;

            if (semop(semid, &mybuf, 1) < 0)
            {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            // sleep(1);

            mybuf.sem_num = 0;
            mybuf.sem_op = -i * 2 - 2;
            mybuf.sem_flg = 0;

            if (semop(semid, &mybuf, 1) < 0)
            {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            size = read(pipe_0[0], resstring, 127);

            if (size < 0)
            {
                printf("Can\'t read string from pipe\n");
                exit(-1);
            }

            printf("Parent got message: %s\n", resstring);

            mybuf.sem_num = 0;
            mybuf.sem_op = i * 2 + 2;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0)
            {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }
            
        }
    }
    else
    {
        /* Child process */
        char *messages[3] = {"Hello, P!", "I am fine, P", "That\'s great!"};

        for (int i = 0; i < n; i++)
        {
            mybuf.sem_num = 0;
            mybuf.sem_op = -i * 2 - 1;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0)
            {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            size = read(pipe_0[0], resstring, 127);

            if (size < 0)
            {
                printf("Can\'t read string from pipe\n");
                exit(-1);
            }

            printf("Child got message: %s\n", resstring);

            size = write(pipe_0[1], messages[i], strlen(messages[i]));

            if (size != strlen(messages[i]))
            {
                printf("Can\'t write all string to pipe from parent to child\n");
                exit(-1);
            }

            printf("Child sent message: %s\n", messages[i]);

            // sleep(1);

            mybuf.sem_num = 0;
            mybuf.sem_op = i * 2 + 2;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0)
            {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }
        }
        mybuf.sem_num = 0;
        mybuf.sem_op = -(n - 1) * 2 - 1;
        mybuf.sem_flg = 0;
        if (semop(semid, &mybuf, 1) < 0)
        {
            printf("Can\'t wait for condition\n");
            exit(-1);
        }
        if (semctl(semid, 0, IPC_RMID) < 0) {
            printf("Failed to delete semaphore\n");
            exit(-1);
        }
    }

    return 0;
}
