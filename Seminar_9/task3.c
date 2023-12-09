#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
    int msqid;
    char pathname[] = "task3.c";
    key_t key;
    int i, len, maxlen;
    pid_t chpid;

    struct mymsgbuf {
       long mtype;
       char mtext[100];
    } mybuf;

    key = ftok(pathname, 0);

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
       printf("Can\'t get msqid\n");
       exit(-1);
    }

    chpid = fork();

    if (chpid < 0) {
        exit(-1);
    }
    else if (chpid == 0) {
        for (int i = 0; i < 5; ++i) {
            maxlen = 100;
            mybuf.mtype = 2;
            strcpy(mybuf.mtext, "Message from Child");
            len = strlen(mybuf.mtext) + 1;
            if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
                printf("Can\'t send message to queue\n");
                msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                exit(-1);
            }

            if ((len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0)) < 0) {
                printf("Can\'t receive message from queue\n");
                exit(-1);
            }
            printf("Child got message: %s\n", mybuf.mtext);
        }
    }
    else {
        for (int i = 0; i < 5; ++i) {
            maxlen = 100;
            mybuf.mtype = 1;
            strcpy(mybuf.mtext, "Message from Parent");
            len = strlen(mybuf.mtext) + 1;
            if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
                printf("Can\'t send message to queue\n");
                msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                exit(-1);
            }

            if ((len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 2, 0)) < 0) {
                printf("Can\'t receive message from queue\n");
                exit(-1);
            }
            printf("Parent got message: %s\n", mybuf.mtext);
        }
    }

    return 0;    
}