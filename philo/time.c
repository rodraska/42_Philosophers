#include "philo.h"

void    ft_meal_time(t_philo *philo)
{
    struct timeval meal_time;

    gettimeofday(&meal_time, NULL);
    pthread_mutex_lock(&(*philo).eat);
    (*philo).times_eaten += 1;
    pthread_mutex_unlock(&(*philo).eat);
    pthread_mutex_lock(&(*philo).meal_time);
    (*philo).last_meal = meal_time.tv_sec * 1000 + meal_time.tv_usec / 1000;
    pthread_mutex_unlock(&(*philo).meal_time);
}

double  get_timestamp(void)
{
    static struct timeval init;
    struct timeval curr;

    gettimeofday(&curr, NULL);
    if (init.tv_sec == 0 && init.tv_usec == 0)
        init = curr;
    
    return(curr.tv_sec * 1000 + curr.tv_usec / 1000.0  - init.tv_sec * 1000 - init.tv_usec / 1000.0);
}

void    my_sleep(long int duration)
{
    double now;

    now = get_timestamp();
    while (get_timestamp() - now < duration)
    {
        if (!check_philos())
            break ;
        usleep(50);
    }
}