#include "philo.h"

void    *routine()
{
    printf("Start Threads\n");
    sleep(3);
    printf("End Thread\n");
}

int main(int ac, char **av)
{
    pthread_t t1;
    pthread_t t2;
  
    if (pthread_create(&t1, NULL, &routine, NULL) != 0)
        return (1);
    if (pthread_create(&t2, NULL, &routine, NULL) != 0)
        return (2);
    if (pthread_join(t1, NULL) != 0)
        return (3);
    if (pthread_join(t2, NULL) != 0)
        return (4);
    return (0);
}