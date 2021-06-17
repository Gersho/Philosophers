/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:05:15 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/15 18:24:49 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

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
	print_args(args);
	args->philos = malloc(sizeof(pthread_t) * args->philo_count);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->philo_count);
	if (!args->philos || !args->forks)
		return (-1);
	gettimeofday(&args->start, NULL);
	mutex_init(args);
	setup_philos(args);
	while (args->all_alive == 1)
		usleep(10);
	shutdown(args);
	return (0);
}