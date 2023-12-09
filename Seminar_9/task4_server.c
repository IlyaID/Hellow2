#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int msqid;
    char pathname[] = "task4_client.c";
    key_t key;
    int i, len, maxlen;
    pid_t chpid;

    struct mymsgbuf {
       long mtype;
       struct inf {
           int proc_id;
           char mtext[100];
       } info;
    } mybuf;

    key = ftok(pathname, 0);

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
       printf("Can\'t get msqid\n");
       exit(-1);
    }

    maxlen = 200;
    for (int i = 0; i < 5; ++i) {
        chpid = fork();
        if (chpid < 0) {
            exit(-1);
        }
        else if (chpid == 0) {
            if ((len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0)) < 0) {
                printf("Can\'t receive message from queue\n");
                exit(-1);
            }
            printf("Server got message from: %d with %s\n", mybuf.info.proc_id, mybuf.info.mtext);
            mybuf.mtype = mybuf.info.proc_id;
            mybuf.info.proc_id = -1;
            strcpy(mybuf.info.mtext, "Message from Server");
            len = sizeof(mybuf.info);
            if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
                printf("Can\'t send message to queue\n");
                msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                exit(-1);
            }
            exit(0);
        }
    }

    return 0;    
}