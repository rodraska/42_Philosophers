#include "philo.h"

int main(void)
{
    pthread_mutex_t mutex1;
    pthread_mutex_t *mutex2;

    pthread_mutex_init(&mutex1, NULL);
    mutex2 = &mutex1; 

    printf("pointer mutex1: %p\n", &mutex1);
    printf("pointer mutex2: %p\n", mutex2);

    return (0);
}