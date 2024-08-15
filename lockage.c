#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void    *add_stuff(void *x)
{
    int *counter;

    counter = (int*)x;
    for (int i = 0; i < 1000000; i++)
        (*counter)++;
    return (NULL);
}

int main()
{
    int x;
    pthread_t threads[5];

    x = 0;
    for (int i = 0; i < 5; i++)
    {
		pthread_create(&threads[i], NULL, &add_stuff, &x);
    }
    for (int i = 0; i < 5; i++)
    {
		pthread_join(threads[i], NULL);
    }
    printf("result: %d\n", x);
}
