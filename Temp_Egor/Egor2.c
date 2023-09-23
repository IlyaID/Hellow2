#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int main()
{
  char* path;
  size_t n;
  n = confstr(_CS_PATH, NULL, (size_t) 0);
  path = malloc(n);
  if(path == NULL) return 0;
  confstr(_CS_PATH, path, n);
  printf("%s\n", getenv("PATH"));
  printf("%s", path);

    return 0;
}