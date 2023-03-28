#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <errno.h>

typedef struct s_philo
{
    pthread_t   philo;
    int         index;
    pthread_mutex_t fork_left;
    pthread_mutex_t *fork_right;
    double      last_meal;
    int         times_eaten;
    int         n_forks;
    
}   t_philo;

typedef struct s_table
{
    t_philo *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t dead;
    int     *fork_use;
    int     nphilo;
    int     t_die;
    int     t_eat;
    int     t_slp;
    int     n_eat;
    int     any_dead;
}   t_table;

int parse_args(int ac, char **av);
int ft_init_threads(t_table mesa);
int ft_join_threads(t_table mesa);
void    *routine(void *arg);
void    *monitor(void *);

int ft_eat(t_philo *philo);
void    ft_rest(t_philo *philo);
int check_philos(void);

void    ft_meal_time(t_philo *philo);
double  get_timestamp(void);

int	ft_atoi(const char *str);
int check_digits(char *str);
t_table *table(void);

#endif