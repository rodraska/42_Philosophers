#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <errno.h>

typedef struct s_philo
{
    pthread_t   philo;
    int         index;     
}   t_philo;

typedef struct s_table
{
    t_philo *philo;
    int     total;
    int     t_die;
    int     t_eat;
    int     t_slp;
}   t_table;

int parse_args(int ac, char **av);

int	ft_atoi(const char *str);
int check_digits(char *str);

#endif