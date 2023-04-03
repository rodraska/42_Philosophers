#include "philo.h"

void    ft_meal_time(t_philo *philo)
{
    struct timeval meal_time;

    gettimeofday(&meal_time, NULL);
    pthread_mutex_lock(&(*philo).eat);
    //printf("times eaten: %d\n", (*philo).times_eaten);
    (*philo).times_eaten += 1;
    pthread_mutex_unlock(&(*philo).eat);
    pthread_mutex_lock(&(*philo).meal_time);
    (*philo).last_meal = meal_time.tv_sec * 1000 + meal_time.tv_usec / 1000;
    //printf("ft_meal_time: %f\n", (*philo).last_meal);
    pthread_mutex_unlock(&(*philo).meal_time);
}

double  get_timestamp(void)
{
    static struct timeval init;
    struct timeval curr;

    gettimeofday(&curr, NULL);
    if (init.tv_sec == 0 && init.tv_usec == 0)
        init = curr;
    //printf("init time: %f\n", init.tv_sec * 1000 + init.tv_usec / 1000.0);
    //printf("curr time: %f\n", curr.tv_sec * 1000 + curr.tv_usec / 1000.0);
    //printf("ret time: %f\n", curr.tv_sec * 1000 + curr.tv_usec / 1000.0  - init.tv_sec * 1000 - init.tv_usec / 1000.0);
    if ((curr.tv_sec * 1000 + curr.tv_usec / 1000.0  - init.tv_sec * 1000 - init.tv_usec / 1000.0) < 0)
        return (0);
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
        //usleep(50);
    }
}

void    check_full(void)
{
    int i;
    int n;

    i = -1;
    n = 0;
    while (++i < table()->nphilo)
    {
        if (table()->philos[i].times_eaten >= table()->n_eat)
         n++;
    }
    table()->n_full = n;
}