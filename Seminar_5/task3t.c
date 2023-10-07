#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define buf_size 400

int main()
{
    int fd;
    size_t size;
    char string[buf_size + 1];

    if ((fd = open("myfile", O_RDONLY)) < 0)
    {
        printf("Can\'t open file\n");
        exit(-1);
    }

    while ((size = read(fd, string, buf_size)) == buf_size)
    {
        fputs(string, stdout);
    }
    
    string[size+1] = '\n';
    fputs(string, stdout);
    
    close(fd);
    
    return 0;
}