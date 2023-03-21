#include "philo.h"

void    *roll_dice()
{
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int));
    *result = value;
    printf("Thread result: %d\n", *result);
    printf("Thread res pointer: %p\n", result);
    return (void *) result;
}

int main(int ac, char **av)
{   
    int *res;
    srand(time(NULL));
    pthread_t th;
    if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
        return (1);
    if (pthread_join(th, (void **) &res) != 0)
        return (2);
    printf("Main result: %d\n", *res);
    printf("Main res ponter: %p\n", res);
    free(res);
    return (0);
}