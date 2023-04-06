/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:39:14 by rreis-de          #+#    #+#             */
/*   Updated: 2023/04/04 17:55:31 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	num = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		num *= 10;
		num += str[i] - 48;
		i++;
	}
	return (num * sign);
}

int	check_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
		{
			write(1, "Invalid argument\n", 17);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

t_table	*table(void)
{
	static t_table	table;

	return (&table);
}

void	ft_free_philos(void)
{
	int	i;

	i = -1;
	while (++i < table()->nphilo)
	{
		pthread_mutex_destroy(&table()->philos[i].fork_left);
		pthread_mutex_destroy(&table()->philos[i].meal_time);
		pthread_mutex_destroy(&table()->philos[i].eat);
		free((void *)table()->philos[i].philo);
	}
	pthread_mutex_destroy(&table()->dead);
	pthread_mutex_destroy(&table()->message);
	pthread_mutex_destroy(&table()->status);
	free((void *)table()->philos);
	free((void *)table()->death);
}

void	ft_message(char *str, double time, int index)
{
	if (table()->any_dead == 1)
		return ;
	pthread_mutex_lock(&table()->message);
	printf("%.0f %d %s\n", time, index, str);
	pthread_mutex_unlock(&table()->message);
}
