/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:20:52 by rreis-de          #+#    #+#             */
/*   Updated: 2023/04/04 19:30:42 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philos(void)
{
	int	dead;
	int	n_full;

	pthread_mutex_lock(&table()->dead);
	dead = table()->any_dead;
	pthread_mutex_unlock(&table()->dead);
	if (dead == 1)
		return (0);
	if (table()->n_eat == -1)
		return (1);
	pthread_mutex_lock(&table()->status);
	n_full = table()->n_full;
	pthread_mutex_unlock(&table()->status);
	if (n_full == table()->nphilo)
		return (0);
	return (1);
}

void	ft_rest(t_philo *philo)
{
	if (!check_philos())
		return ;
	ft_message(SLEEP, get_timestamp(), philo->index);
	my_sleep(table()->t_slp);
	if (!check_philos())
		return ;
	ft_message(THINK, get_timestamp(), philo->index);
}

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&(*philo).fork_left);
	ft_message(FORK, get_timestamp(), philo->index);
	pthread_mutex_lock((*philo).fork_right);
	ft_message(FORK, get_timestamp(), philo->index);
	ft_meal_time(philo);
	ft_message(EAT, get_timestamp(), philo->index);
	my_sleep(table()->t_eat);
	pthread_mutex_unlock(&(*philo).fork_left);
	pthread_mutex_unlock((*philo).fork_right);
	return (1);
}
