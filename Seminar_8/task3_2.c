#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    int semid;
    char sempathname[] = "task3_1.c";
    key_t key_sem;
    struct sembuf mybuf;

    key_sem = ftok(sempathname, 0);

    if ((semid = semget(key_sem, 1, 0666 | IPC_CREAT | IPC_EXCL)) < 0)
    {
        printf("Semaphore exists\n");
        if ((semid = semget(key_sem, 1, 0666 | IPC_CREAT)) < 0)
        {
            printf("Can\'t create semaphore set\n");
            exit(-1);
        }
    }
    else
    {
        if ((semid = semget(key_sem, 1, 0666 | IPC_CREAT)) < 0)
        {
            printf("Can\'t create semaphore set\n");
            exit(-1);
        }
        else
        {
            printf("Semaphore was created\n");
            mybuf.sem_num = 0;
            mybuf.sem_op = 1;
            mybuf.sem_flg = 0;

            if (semop(semid, &mybuf, 1) < 0)
            {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }
        }
    }

    mybuf.sem_num = 0;
    mybuf.sem_op = -1;
    mybuf.sem_flg = 0;

    int *array;
    int shmid;
    int new = 1;
    char pathname[] = "06-3a.c";
    key_t key;
    long i;

    if ((key = ftok(pathname, 0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((shmid = shmget(key, 3 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0)
    {
        if (errno != EEXIST)
        {
            printf("Can\'t create shared memory\n");
            exit(-1);
        }
        else
        {
            if ((shmid = shmget(key, 3 * sizeof(int), 0)) < 0)
            {
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
            new = 0;
        }
    }

    if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1))
    {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    mybuf.sem_op = -1;
    if (semop(semid, &mybuf, 1) < 0)
    {
        printf("Can\'t wait for condition\n");
        exit(-1);
    }
    else
    {
        printf("B enterig\n");
        if (new)
        {
            array[0] = 1;
            array[1] = 0;
            array[2] = 1;
        }
        else
        {
            array[1] += 1;
            for (i = 0; i < 2000000000L; i++)
                ;
            array[2] += 1;
        }

        printf("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n", array[0], array[1], array[2]);

        if (shmdt(array) < 0)
        {
            printf("Can't detach shared memory\n");
            exit(-1);
        }
        printf("B exiting\n");
    }
    mybuf.sem_op = 1;
    semop(semid, &mybuf, 1);

    return 0;
}
