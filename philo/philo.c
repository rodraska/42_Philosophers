#include "philo.h"

int mails = 0;
pthread_mutex_t mutex;

/* void    *routine()
{
    printf("Start Thread\n");
    sleep(3);
    printf("End Thread\n");
} */

/* void    *routine(void *arg)
{  
    t_philo *filo = (t_philo *)arg;

    printf("index: %d\n", (*filo).index);
    for (int i = 0; i < 100; i++)
    {
        pthread_mutex_lock(&(*filo).fork);
        if ((*filo).index > -1)
            mails++;
        pthread_mutex_unlock(&(*filo).fork);
    }
} */

void    *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    printf("philo: %d, fork_left: %p, fork_right: %p\n", philo->index, &philo->fork_left, philo->fork_right);

}

int ft_join_threads(t_table mesa)
{
    int i;

    i = 0;
    while (++i < mesa.nphilo)
    {
        if (pthread_join(mesa.philos[i].philo, NULL))
        {
            printf("Error joining thread\n");
            return (-1);
        }
    }
    return (0);
}

int ft_init_threads(t_table mesa)
{
    int i;

    i = -1;
    while (++i < mesa.nphilo)
    {
        mesa.curr = i;
        if (pthread_create(&mesa.philos[i].philo, NULL, &routine, &mesa.philos[i]) != 0)
        {
            printf("Error creating thread\n");
            return (-1);
        }
    }
    return (0);
}

void    ft_table(int ac, char **av)
{
    t_table mesa;
    int     i;

    i = -1;
    mesa.nphilo = ft_atoi(av[1]);
    mesa.philos = (t_philo *)malloc(sizeof(t_philo) * mesa.nphilo);
    mesa.fork_use = (int *)malloc(sizeof(int) * mesa.nphilo);
    while (++i < mesa.nphilo)
    {
        mesa.philos[i].philo = (pthread_t)malloc(sizeof(pthread_t));
        mesa.philos[i].index = i;
        pthread_mutex_init(&mesa.philos[i].fork_left, NULL);
        if (i < mesa.nphilo - 1)
            mesa.philos[i].fork_right = &mesa.philos[i + 1].fork_left;
        else
            mesa.philos[i].fork_right = &mesa.philos[0].fork_left;
    }
    /* i = -1;
    while (++i < mesa.nphilo)
    {
        printf("fork_left of philo %d: %p\n", i, &mesa.philos[i].fork_left);
        printf("fork_right of philo %d: %p\n", i, mesa.philos[i].fork_right);
    } */
    mesa.t_die = ft_atoi(av[2]);
    mesa.t_eat = ft_atoi(av[3]);
    mesa.t_slp = ft_atoi(av[4]);
    ft_init_threads(mesa);
    ft_join_threads(mesa);
    printf("number of mails: %d\n", mails);
}

int parse_args(int ac, char **av)
{
    int i;

    i = 0;
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
            //write(1, "Success\n", 8);
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