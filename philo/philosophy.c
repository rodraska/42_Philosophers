/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:30:03 by rreis-de          #+#    #+#             */
/*   Updated: 2023/04/04 19:11:24 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_table2(int ac, char **av)
{
	table()->t_die = ft_atoi(av[2]);
	table()->t_eat = ft_atoi(av[3]);
	table()->t_slp = ft_atoi(av[4]);
	table()->n_full = 0;
	pthread_mutex_init(&table()->dead, NULL);
	pthread_mutex_init(&table()->message, NULL);
	pthread_mutex_init(&table()->status, NULL);
	if (ac == 5)
		table()->n_eat = -1;
	else
		table()->n_eat = ft_atoi(av[5]);
	ft_init_threads(*table());
	ft_join_threads(*table());
	ft_free_philos();
}

void	ft_table(int ac, char **av)
{
	int	i;

	i = -1;
	table()->nphilo = ft_atoi(av[1]);
	table()->philos = (t_philo *)malloc(sizeof(t_philo) * table()->nphilo);
	table()->death = (pthread_t)malloc(sizeof(pthread_t));
	while (++i < table()->nphilo)
	{
		table()->philos[i].philo = (pthread_t *)malloc(sizeof(pthread_t));
		table()->philos[i].index = i + 1;
		table()->philos[i].last_meal = 0;
		table()->philos[i].times_eaten = 0;
		pthread_mutex_init(&table()->philos[i].fork_left, NULL);
		pthread_mutex_init(&table()->philos[i].meal_time, NULL);
		pthread_mutex_init(&table()->philos[i].eat, NULL);
		if (i < table()->nphilo - 1)
			table()->philos[i].fork_right = &table()->philos[i + 1].fork_left;
		else
			table()->philos[i].fork_right = &table()->philos[0].fork_left;
	}
	ft_table2(ac, av);
}

int	parse_args(int ac, char **av)
{
	int	i;

	i = 0;
	get_timestamp();
	while (++i < ac)
	{
		if (av[i][0] == '\0')
			return (EXIT_FAILURE);
		if (check_digits(av[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (i == 1 && ft_atoi(av[1]) > 200)
		{
			write(1, "Invalid number of philosophers\n", 31);
			return (EXIT_FAILURE);
		}
		if (i > 1 && ft_atoi(av[i]) > 1000000)
		{
			write(1, "Invalid input. Number too big\n", 30);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (parse_args(ac, av) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else
		{
			if (ft_atoi(av[1]) == 1)
			{
				philo_one(ft_atoi(av[2]) * 1000);
				return (EXIT_FAILURE);
			}
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
