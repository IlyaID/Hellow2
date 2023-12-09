#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int msqid;
char pathname[] = "task5.c";
key_t key;
int i, len, maxlen;
pid_t chpid;

struct mymsgbuf {
   long mtype;
   int val;
} mybuf;

void A(int* semval, int val) {
    *semval += val;
}

void D(int* semval, int val) {
    while (*semval < val);
    *semval -= val;
}

void Z(int* semval) {
    while (*semval != 0);
}

int main() {
    int semval = 0;
    key = ftok(pathname, 0);
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t get msqid\n");
        exit(-1);
    }
    maxlen = 100;

    len = sizeof(int);
    mybuf.mtype = 1;
    mybuf.val = 11;
    chpid = fork();
    if (chpid < 0) {
        exit(-1);
    }
    else if (chpid == 0) {
        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
        exit(0);
    }
    else {
        if ((len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0)) < 0) {
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }
        if (mybuf.mtype == 1) {
            printf("Value of sem before A: %d\n", semval);
            A(&semval, mybuf.val);
            printf("Value of sem after A: %d\n", semval);
            if (semval == 11) {
                printf("Test for A-sem_op is successful\n\n");
            }
            else {
                printf("Error in test for A-sem_op\n");
                exit(-1);
            }
        }
        else {
            printf("Error sem_op type\n");
            exit(-1);
        }
    }

    len = sizeof(int);
    semval = 0;
    mybuf.mtype = 2;
    mybuf.val = 0;
    chpid = fork();
    if (chpid < 0) {
        exit(-1);
    }
    else if (chpid == 0) {
        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
        exit(0);
    }
    else {
        if ((len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 2, 0)) < 0) {
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }
        if (mybuf.mtype == 2) {
            printf("Value of sem before A and D: %d\n", semval);
            A(&semval, 15);
            printf("Value of sem after A and before D: %d\n", semval);
            D(&semval, 15);
            printf("Value of sem after A and after D: %d\n", semval);
            if (semval == 0) {
                printf("Test for D-sem_op is successful\n\n");
            }
            else {
                printf("Error in test for D-sem_op\n");
                exit(-1);
            }
        }
        else {
            printf("Error sem_op type\n");
            exit(-1);
        }
    }

    len = sizeof(int);
    semval = 17;
    mybuf.mtype = 3;
    mybuf.val = 0;
    chpid = fork();
    if (chpid < 0) {
        exit(-1);
    }
    else if (chpid == 0) {
        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
        exit(0);
    }
    else {
        if ((len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 3, 0)) < 0) {
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }
        if (mybuf.mtype == 3) {
            printf("Value of sem: %d\n", semval);
            D(&semval, 17);
            printf("Value of sem after D and before Z: %d\n", semval);
            Z(&semval);
            printf("Value of sem after Z: %d\n", semval);
            if (semval == 0) {
                printf("Test for Z-sem_op is successful\n\n");
            }
            else {
                printf("Error in test for Z-sem_op\n");
                exit(-1);
            }
        }
        else {
            printf("Error sem_op type\n");
            exit(-1);
        }
    }

    return 0;
}