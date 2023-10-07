#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
int main() {
    int fd[2], fd1[2], result;
    size_t size, size1;
    char string[15], string1[15];
    if(pipe(fd)<0){
        printf("Can\'t create pipe1");
        exit(-1);
    }
    if(pipe(fd1)<0) {
        printf("Can\'t create pipe2");
        exit(-1);
    }
    result=fork();
    if(result>0){
        size=write(fd[1],"Hi, student1!\n",15);
        size1=read(fd1[0],string,15);
        printf("%s", string);
        if(size1!=15) {
            printf("Can\'t read string");
            exit(-1); 
        }
       close(fd[1]);
       close(fd1[0]);
    }
    if(result==0) {
        size=read(fd[0],string1,15);
        size1=write(fd1[1],"Hi, student2!\n",15);
        printf("%s", string1);
        if(size!=15) {
            printf("Can\'t read string");
            exit(-1); 
    }
   close(fd[0]);
   close(fd1[1]);
 }  
 return 0;
 }