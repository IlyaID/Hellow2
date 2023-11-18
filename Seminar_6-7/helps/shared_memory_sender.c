#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

#define INIT_BUFSIZE 8

int main()
{
    char *array;
    int shmid;
    char pathname[] = "shared_memory_sender.c";
    //char pathname[] = "test";
    key_t key;

    int fd;
    int source_size = INIT_BUFSIZE;
    char *source = calloc(sizeof(char), source_size);

    if ((fd = open(pathname, O_RDONLY)) < 0)
    {
        printf("Can\'t open file\n");
        exit(-1);
    }

    while (read(fd, source + source_size / 2 - INIT_BUFSIZE / 2, source_size / 2) == source_size / 2)
    {
        source_size *= 2;
        source = realloc(source, source_size);
        if (!source)
        {
            printf("Can't realloc\n");
            exit(-1);
        }
    }

    if ((key = ftok(pathname, 0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((shmid = shmget(key, source_size * sizeof(char), 0666 | IPC_CREAT | IPC_EXCL)) < 0)
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
        }
    }

    if ((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1))
    {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    for (int i = 0; i < source_size; i++)
    {
        array[i] = source[i];
    }

    if (shmdt(array) < 0)
    {
        printf("Can't detach shared memory\n");
        exit(-1);
    }

    return 0;
}
