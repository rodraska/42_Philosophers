#include "philo.h"

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void    *routine(void *arg)
{
    int index = *(int *)arg;
    printf("%d ", primes[index]);
    free(arg);
}

int main(int ac, char **av)
{
    pthread_t th[10];
    int i;
    for (i = 0; i < 10; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0)
            perror("Failed to create thread\n");
    }
    for (i = 0; i < 10; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
            perror("Failed to join thread\n");
    }
    return (0);
}