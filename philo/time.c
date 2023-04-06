/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:39:51 by rreis-de          #+#    #+#             */
/*   Updated: 2023/04/04 19:35:02 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_meal_time(t_philo *philo)
{
	struct timeval	meal_time;

	gettimeofday(&meal_time, NULL);
	pthread_mutex_lock(&(*philo).eat);
	(*philo).times_eaten += 1;
	pthread_mutex_unlock(&(*philo).eat);
	pthread_mutex_lock(&(*philo).meal_time);
	(*philo).last_meal = meal_time.tv_sec * 1000 + meal_time.tv_usec / 1000;
	pthread_mutex_unlock(&(*philo).meal_time);
}

double	get_timestamp(void)
{
	static struct timeval	init;
	struct timeval			curr;
	double					time;

	gettimeofday(&curr, NULL);
	if (init.tv_sec == 0 && init.tv_usec == 0)
		init = curr;
	time = curr.tv_sec * 1000 + curr.tv_usec / 1000.0 \
	- init.tv_sec * 1000 - init.tv_usec / 1000.0;
	if (time < 0)
		return (0);
	return (time);
}

void	my_sleep(long int duration)
{
	double	now;

	now = get_timestamp();
	while (get_timestamp() - now < duration)
	{
		if (!check_philos())
			break ;
	}
}

int	check_full(void)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (++i < table()->nphilo)
	{
		pthread_mutex_lock(&table()->philos[i].eat);
		if (table()->philos[i].times_eaten >= \
		table()->n_eat && table()->n_eat != -1)
			n++;
		pthread_mutex_unlock(&table()->philos[i].eat);
	}
	return (n);
}

void	philo_one(int t_die)
{
	ft_message(FORK, get_timestamp(), 1);
	usleep(t_die);
	ft_message(DIE, get_timestamp(), 1);
}
