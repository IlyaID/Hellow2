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
            int pid = getpid();
            mybuf.mtype = 1;
            mybuf.info.proc_id = pid;
            strcpy(mybuf.info.mtext, "Message from Client");
            len = sizeof(mybuf.info) + 1;
            if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
                printf("Can\'t send message to queue\n");
                msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                exit(-1);
            }
            if ((len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, pid, 0)) < 0) {
                printf("Can\'t receive message from queue\n");
                exit(-1);
            }
            printf("Client got message from Server: %s\n", mybuf.info.mtext);
        }
        else {
            exit(0);
        }
    }
    return 0;
}