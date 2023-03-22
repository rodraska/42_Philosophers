#include "philo.h"

/* void    *routine()
{
    printf("Start Thread\n");
    sleep(3);
    printf("End Thread\n");
} */

int mails = 0;
pthread_mutex_t mutex;

void    *routine()
{
    for (int i = 0; i < 100; i++)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

int ft_join_threads(t_table mesa)
{
    int i;

    i = 0;
    while (++i < mesa.nphilo)
    {
        if (pthread_join(mesa.philos[i], NULL))
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
        if (pthread_create(&mesa.philos[i], NULL, &routine, NULL) != 0)
        {
            printf("Error creating thread\n");
            return (-1);
        }
    }
    ft_join_threads(mesa);
    return (0);
}

void    ft_table(int ac, char **av)
{
    t_table mesa;
    int     i;

    i = -1;
    mesa.nphilo = ft_atoi(av[1]);
    mesa.philos = (pthread_t *)malloc(sizeof(pthread_t) * mesa.nphilo);
    while (++i < mesa.nphilo)
        mesa.philos[i] = (pthread_t)malloc(sizeof(pthread_t));
    mesa.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * mesa.nphilo);
    i = -1;
    while (++i < mesa.nphilo)
        pthread_mutex_init(&mesa.forks[i], NULL);
    mesa.t_die = ft_atoi(av[2]);
    mesa.t_eat = ft_atoi(av[3]);
    mesa.t_slp = ft_atoi(av[4]);
    ft_init_threads(mesa);
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