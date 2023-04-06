/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:08:29 by rreis-de          #+#    #+#             */
/*   Updated: 2023/04/04 19:36:18 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < table()->nphilo)
		{
			if (check_full() == table()->nphilo)
			{
				pthread_mutex_lock(&table()->dead);
				table()->any_dead = 1;
				pthread_mutex_unlock(&table()->dead);
				return (NULL);
			}
			if (!ft_hunger(&table()->philos[i]))
				return (NULL);
		}
	}
	return (NULL);
}

int	ft_hunger(t_philo *philo)
{
	struct timeval	curr_time;
	double			time_last_meal;

	time_last_meal = 0;
	gettimeofday(&curr_time, NULL);
	pthread_mutex_lock(&philo->meal_time);
	if (philo->last_meal != 0)
		time_last_meal = curr_time.tv_sec * 1000 + \
		curr_time.tv_usec / 1000 - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_time);
	if (time_last_meal >= table()->t_die)
	{
		ft_message(DIE, get_timestamp(), philo->index);
		pthread_mutex_lock(&table()->dead);
		table()->any_dead = 1;
		pthread_mutex_unlock(&table()->dead);
		return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((*philo).index % 2 != 0)
		usleep(2500);
	while (1)
	{
		if (!check_philos())
			break ;
		if (ft_eat(philo))
			ft_rest(philo);
		else
			break ;
	}
	return (NULL);
}

int	ft_join_threads(t_table mesa)
{
	int	i;

	i = -1;
	while (++i < mesa.nphilo)
	{
		if (pthread_join(*mesa.philos[i].philo, NULL))
		{
			printf("Error joining thread\n");
			return (-1);
		}
	}
	return (0);
}

int	ft_init_threads(t_table mesa)
{
	int	i;

	i = -1;
	while (++i < mesa.nphilo)
	{
		if (pthread_create(mesa.philos[i].philo, NULL, \
		&routine, &mesa.philos[i]) != 0)
		{
			printf("Error creating thread\n");
			return (-1);
		}
		usleep(100);
	}
	monitor();
	return (0);
}
