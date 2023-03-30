#include "philo.h"

int check_philos(void)
{
    int i;
    int f;

    pthread_mutex_lock(&table()->dead);
    if (table()->any_dead == 1)
    {
        pthread_mutex_unlock(&table()->dead);
        return (0);
    }
    pthread_mutex_unlock(&table()->dead);
    i = -1;
    f = 0;
    if (table()->n_eat == -1)
        return (1);
    while (++i < table()->nphilo)
    {
        pthread_mutex_lock(&table()->philos[i].eat);
        if (table()->philos[i].times_eaten < table()->n_eat)
            f = 1;
        pthread_mutex_unlock(&table()->philos[i].eat);
    }
    if (f == 0)
        return (0);
    return (1);
}

void    ft_rest(t_philo *philo)
{
    if (!check_philos())
        return ;
    ft_message(SLEEP, get_timestamp(), philo->index);
    //printf("%.0f %d is sleeping\n", get_timestamp(), philo->index);
    //usleep(table()->t_slp * 1000);
    my_sleep(table()->t_slp);
    if (!check_philos())
        return ;
    ft_message(THINK, get_timestamp(), philo->index);
    //printf("%.0f %d is thinking\n", get_timestamp(), philo->index);
}

int ft_eat_odd(t_philo *philo)
{
    pthread_mutex_lock(&(*philo).fork_left);
    if (!check_philos())
    {
        pthread_mutex_unlock(&(*philo).fork_left);
        return (0);
    }
    ft_message(FORK, get_timestamp(), philo->index);
    //printf("%.0f %d has taken a fork\n", get_timestamp(), philo->index);
    pthread_mutex_lock((*philo).fork_right);
    if (!check_philos())
    {
        pthread_mutex_unlock(&(*philo).fork_left);
        pthread_mutex_unlock((*philo).fork_right);
        return (0);
    }
    ft_message(FORK, get_timestamp(), philo->index);
    //printf("%.0f %d has taken a fork\n", get_timestamp(), philo->index);
    ft_meal_time(philo);
    ft_message(EAT, get_timestamp(), philo->index);
    //printf("%.0f %d is eating\n", get_timestamp(), philo->index);
    my_sleep(table()->t_eat);
    //usleep(table()->t_eat * 1000);
    pthread_mutex_unlock(&(*philo).fork_left);
    pthread_mutex_unlock((*philo).fork_right);
    return (1);
}

int ft_eat_even(t_philo *philo)
{
    pthread_mutex_lock((*philo).fork_right);
    if (!check_philos())
    {
        pthread_mutex_unlock((*philo).fork_right);
        return (0);
    }
    ft_message(FORK, get_timestamp(), philo->index);
    //printf("%.0f %d has taken a fork\n", get_timestamp(), philo->index);
    pthread_mutex_lock(&(*philo).fork_left);
    if (!check_philos())
    {
        pthread_mutex_unlock((*philo).fork_right);
        pthread_mutex_unlock(&(*philo).fork_left);
        return (0);
    }
    ft_message(FORK, get_timestamp(), philo->index);
    //printf("%.0f %d has taken a fork\n", get_timestamp(), philo->index);
    ft_meal_time(philo);
    ft_message(EAT, get_timestamp(), philo->index);
    //printf("%.0f %d is eating\n", get_timestamp(), philo->index);
    usleep(table()->t_eat * 1000);
    pthread_mutex_unlock((*philo).fork_right);
    pthread_mutex_unlock(&(*philo).fork_left);
    return (1);
}

int ft_eat(t_philo *philo)
{
    if ((*philo).index % 2 == 0)
    {
        if(!ft_eat_even(philo))
            return (0);
    } 
    else
    {
        if (!ft_eat_odd(philo))
        return (0);
    }
    return (1);
}