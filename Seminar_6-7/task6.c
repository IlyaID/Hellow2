#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

int fib(int n)
{
    if (n < 2)
        return 1;
    else
        return fib(n - 1) + fib(n - 2);
}

void *mythread_1(void *dummy)

{

    pthread_t mythid;

    mythid = pthread_self();

    a = fib(1);

    printf("Thread %u, Calculation result = %d\n", mythid, a);

    return NULL;
}

void *mythread_2(void *dummy)

{

    pthread_t mythid;

    mythid = pthread_self();

    a = fib(*(int*)dummy);

    printf("Thread %u, Calculation result = %d\n", mythid, a);

    return NULL;
}

int main()
{
    pthread_t thid_1, thid_2, thid_3, mythid;
    int result_1, result_2, result_3;

    int n1 = 5, n2 = 10;

    result_1 = pthread_create(&thid_1, (pthread_attr_t *)NULL, mythread_1, NULL);
    result_2 = pthread_create(&thid_2, (pthread_attr_t *)NULL, mythread_2, &n1);
    result_3 = pthread_create(&thid_3, (pthread_attr_t *)NULL, mythread_2, &n2);

    if (result_1 != 0)
    {
        printf("Error on thread 1 create, return value = %d\n", result_1);
        exit(-1);
    }

    if (result_2 != 0)
    {
        printf("Error on thread 2 create, return value = %d\n", result_2);
        exit(-1);
    }

    if (result_3 != 0)
    {
        printf("Error on thread 3 create, return value = %d\n", result_3);
        exit(-1);
    }

    printf("Thread 1 created, thid = %u\n", thid_1);
    printf("Thread 2 created, thid = %u\n", thid_2);
    printf("Thread 3 created, thid = %u\n", thid_3);

    mythid = pthread_self();

    a = fib(15);

    printf("Thread %u, Calculation result = %d\n", mythid, a);

    pthread_join(thid_1, (void **)NULL);
    pthread_join(thid_2, (void **)NULL);
    pthread_join(thid_3, (void **)NULL);

    return 0;
}
