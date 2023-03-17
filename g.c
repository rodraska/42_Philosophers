#include "philo.h"

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0;

void    *fuel_filling()
{
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutexFuel);
        fuel += 15;
        printf("Filled fuel...%d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_signal(&condFuel);
        sleep(1);
    }
        
}

void    *car()
{
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40)
    {
        printf("No fuel. Waiting...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
    }
    fuel -= 40;
    printf("Got Fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}

int main(int ac, char **av)
{
    pthread_t th[2];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    for (int i = 0; i < 2; i++)
    {
        if (i == 1)
        {
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
                perror("Failed to create thread\n");
        }
        else
        {
            if (pthread_create(&th[i], NULL, &car, NULL) != 0)
                perror("Failed to create thread\n");
        }
    }
    for (int i = 0; i < 2; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
            perror("Failed to join thread");
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return (0);
}