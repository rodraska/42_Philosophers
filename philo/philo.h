/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:10:37 by rreis-de          #+#    #+#             */
/*   Updated: 2023/04/04 19:10:38 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <errno.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_philo
{
	pthread_t		*philo;
	int				index;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	meal_time;
	pthread_mutex_t	eat;
	double			last_meal;
	int				times_eaten;
	int				dead;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	pthread_t		death;
	pthread_mutex_t	dead;
	pthread_mutex_t	message;
	pthread_mutex_t	status;
	int				*fork_use;
	int				nphilo;
	int				t_die;
	int				t_eat;
	int				t_slp;
	int				n_eat;
	int				any_dead;
	int				n_full;
}	t_table;

void	ft_table2(int ac, char **av);
void	ft_table(int ac, char **av);
int		parse_args(int ac, char **av);

int		ft_init_threads(t_table mesa);
int		ft_join_threads(t_table mesa);
void	*routine(void *arg);
void	*monitor(void);
int		ft_hunger(t_philo *philo);

int		ft_eat(t_philo *philo);
void	ft_rest(t_philo *philo);
int		check_philos(void);

void	ft_meal_time(t_philo *philo);
double	get_timestamp(void);
void	my_sleep(long int duration);
int		check_full(void);
void	philo_one(int t_die);

int		ft_atoi(const char *str);
int		check_digits(char *str);
t_table	*table(void);
void	ft_free_philos(void);
void	ft_message(char *str, double time, int index);

#endif