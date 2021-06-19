/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:05:15 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/19 14:19:40 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	error_ret(void)
{
	write(1, "Error\n", 6);
	return (-1);
}

int	shutdown(t_args *args)
{
	mutex_destroy(args);
	unspawn_philos(args);
	free(args->philos);
	free(args->forks);
	free(args);
	free(args->philo_data);
	return (0);
}

int	main_monitoring(t_args *args)
{
	int	now;
	int	i;

	while (args->all_alive == 1)
	{
		if (args->meal_count != -1)
		{
			if (args->philo_full >= args->philo_count)
			{
				args->all_alive = 0;
				break ;
			}
		}
		i = 0;
		while (i < args->philo_count)
		{
			now = get_elapsed_time(args->start);
			if (now == -1)
				return (-1);
			philo_isalive(args->philo_data[i], now);
			i++;
		}
		usleep(1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_args	*args;

	if (ac != 5 && ac != 6)
		return (error_ret());
	args = malloc(sizeof(t_args));
	if (!args)
		return (-1);
	args_init(args);
	if (args_parse(ac, av, args) == -1)
		return (error_ret());
	args->philos = malloc(sizeof(pthread_t) * args->philo_count);
	args->philo_data = malloc(sizeof(t_philo *) * args->philo_count);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->philo_count);
	if (!args->philos || !args->forks || !args->philo_data)
		return (-1);
	gettimeofday(&args->start, NULL);
	mutex_init(args);
	setup_philos(args);
	if (main_monitoring(args) == -1)
		return (-1);
	shutdown(args);
	return (0);
}
