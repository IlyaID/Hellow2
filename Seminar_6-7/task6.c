#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *mythread(void *dummy)


{

   pthread_t mythid;
   
   mythid = pthread_self();

   a = a+1;

   printf("Thread %u, Calculation result = %d\n", mythid, a);

   return NULL;
}

int main()
{
   pthread_t thid, thid_1, mythid; 
   int       result, result1;

   result = pthread_create( &thid, (pthread_attr_t *)NULL, mythread, NULL);
   result1 = pthread_create( &thid_1, (pthread_attr_t *)NULL, mythread, NULL);
   
   if(result != 0){
      printf ("Error on thread create, return value = %d\n", result);
      exit(-1);
   }   
   
   if(result1 != 0){
         printf ("Error on thread create, return value = %d\n", result);
         exit(-1);
      }   

   printf("Thread created, thid = %u\n", thid);
   printf("Thread created, thid = %u\n", thid_1);
   mythid = pthread_self();
   
   a = a+1;
   
   printf("Thread %u, Calculation result = %d\n", mythid, a);

   pthread_join(thid, (void **)NULL);
   pthread_join(thid_1, (void **)NULL);
   return 0;
}
