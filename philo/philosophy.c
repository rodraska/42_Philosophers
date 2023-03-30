#include "philo.h"

void    *monitor(void *arg)
{
    struct timeval curr_time;
    double time_last_meal;
    arg = NULL;
    int i;

    while (1)
    {
        i = -1;
        while (++i < table()->nphilo)
        {
            gettimeofday(&curr_time, NULL);
            pthread_mutex_lock(&table()->philos[i].meal_time);
            if (table()->philos[i].last_meal != 0)
                time_last_meal = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000 - table()->philos[i].last_meal;
            pthread_mutex_unlock(&table()->philos[i].meal_time);
            if (time_last_meal >= table()->t_die)
            {
                pthread_mutex_lock(&table()->dead);
                table()->any_dead = 1;
                pthread_mutex_unlock(&table()->dead);
                printf("%.0f %d died\n", get_timestamp(),table()->philos[i].index);
                return (NULL);
            }
        }
        //usleep(1000);
    }
    return (NULL);
}

void    *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        if(table()->any_dead == 1)
            break ;
        if (ft_eat(philo))
            ft_rest(philo);
        else
            break ;
    }
    return (NULL);
}

int ft_join_threads(t_table mesa)
{
    int i;

    i = -1;
    while (++i < mesa.nphilo)
    {
        if (pthread_join(mesa.philos[i].philo, NULL))
        {
            printf("Error joining thread\n");
            return (-1);
        }
    }
    i = -1;
    while (++i < mesa.nphilo)
    {
        pthread_mutex_destroy(&mesa.philos[i].fork_left);
        pthread_mutex_destroy(&mesa.philos[i].meal_time);
        pthread_mutex_destroy(&mesa.philos[i].eat);
    }
    pthread_mutex_destroy(&mesa.dead);
    return (0);
}

int ft_init_threads(t_table mesa)
{
    int i;

    i = -1;
    pthread_t death;

    get_timestamp();
    while (++i < mesa.nphilo)
    {
        if (pthread_create(&mesa.philos[i].philo, NULL, &routine, &mesa.philos[i]) != 0)
        {
            printf("Error creating thread\n");
            return (-1);
        }
        usleep(100);
    }
    if (pthread_create(&death, NULL, &monitor, NULL) != 0)
    {
        printf("Error creating thread\n");
        return (-1);
    }
    return (0);
}

void    ft_table(int ac, char **av)
{
    int     i;

    i = -1;
    printf("%c" ,'\0');
    table()->nphilo = ft_atoi(av[1]);
    table()->philos = (t_philo *)malloc(sizeof(t_philo) * table()->nphilo);
    while (++i < table()->nphilo)
    {
        table()->philos[i].philo = (pthread_t)malloc(sizeof(pthread_t));
        table()->philos[i].index = i + 1;
        pthread_mutex_init(&table()->philos[i].fork_left, NULL);
        pthread_mutex_init(&table()->philos[i].meal_time, NULL);
        pthread_mutex_init(&table()->philos[i].eat, NULL);
        if (i < table()->nphilo - 1)
            table()->philos[i].fork_right = &table()->philos[i + 1].fork_left;
        else
            table()->philos[i].fork_right = &table()->philos[0].fork_left;  
    }
    table()->t_die = ft_atoi(av[2]);
    table()->t_eat = ft_atoi(av[3]);
    table()->t_slp = ft_atoi(av[4]);
    pthread_mutex_init(&table()->dead, NULL);
    if (ac == 5)
        table()->n_eat = -1;
    else
        table()->n_eat = ft_atoi(av[5]);
    ft_init_threads(*table());
    ft_join_threads(*table());
    ft_free_philos();
}

int parse_args(int ac, char **av)
{
    int i;

    i = 0;
    get_timestamp();
    while (++i < ac)
    {
        if (check_digits(av[i]) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        if (i == 1 && ft_atoi(av[1]) > 200)
        {
            write(1, "Invalid number of philosophers\n", 31);
            return (EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    if (ac == 5 || ac == 6)
    {   
        if (parse_args(ac, av) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        else
        {
            ft_table(ac, av);
            return (EXIT_SUCCESS);
        }
    }
    else
    {
        write(1, "Invalid number of arguments\n", 28);
        return (EXIT_FAILURE);
    }
}