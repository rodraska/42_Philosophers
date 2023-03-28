#include "philo.h"

int check_philos(void)
{
    if (table()->any_dead == 1)
        return (0);
    return (1);
}

void    ft_rest(t_philo *philo)
{
    if (!check_philos())
        return ;
    printf("%.0f %d is sleeping\n", get_timestamp(), philo->index);
    usleep(table()->t_slp * 1000);
    if (!check_philos())
        return ;
    printf("%.0f %d is thinking\n", get_timestamp(), philo->index);
}

int ft_eat(t_philo *philo)
{
    pthread_mutex_lock(&(*philo).fork_left);
    if (!check_philos())
    {
        pthread_mutex_unlock(&(*philo).fork_left);
        return (0);
    }
    printf("%.0f %d has taken a fork\n", get_timestamp(), philo->index);
    pthread_mutex_lock((*philo).fork_right);
    if (!check_philos())
    {
        pthread_mutex_unlock(&(*philo).fork_left);
        pthread_mutex_unlock((*philo).fork_right);
        return (0);
    }
    printf("%.0f %d has taken a fork\n", get_timestamp(), philo->index);
    ft_meal_time(philo);
    printf("%.0f %d is eating\n", get_timestamp(), philo->index);
    usleep(table()->t_eat * 1000);
    pthread_mutex_unlock(&(*philo).fork_left);
    pthread_mutex_unlock((*philo).fork_right);
    return (1);
}