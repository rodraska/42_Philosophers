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
    pthread_mutex_t fork_left;
    pthread_mutex_t *fork_right;
    int         n_forks;
}   t_philo;

typedef struct s_table
{
    t_philo *philos;
    pthread_mutex_t *forks;
    int     *fork_use;
    int     nphilo;
    int     t_die;
    int     t_eat;
    int     t_slp;
}   t_table;

int parse_args(int ac, char **av);
void    ft_table(int ac, char **av);
int ft_init_threads(t_table mesa);
int ft_join_threads(t_table mesa);
void    *routine(void *arg);

int	ft_atoi(const char *str);
int check_digits(char *str);

#endif