#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
int main() {
    int pfd;
    int fd[2];
    char a[100];
    int c,b;
    int size;
    if ((pfd = pipe(fd) < 0)) {
        printf("ошибка");
        exit(1);
    }
    else {
        while(c != b) {
            c = write(fd[1],"h",2);
            b = read(fd[0],a,1);
            size++;
            printf("%d\n",size);
        }
    //printf("%d\n",size);
    return 0;
    }
}