/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:05:15 by kzennoun          #+#    #+#             */
/*   Updated: 2021/05/21 16:32:21 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args	args;

	if (ac != 5 && ac != 6)
	{
		write(1, "Error\n", 6);
		exit(-1);
	}
	args_init(&args);
	args_parse(ac, av, &args);
	print_args(&args);
	exit(0);
}

/* 
philosopher with threads and mutex

args:
		number_of_philosophers
		time_to_die 
		time_to_eat
		time_to_sleep
		optional->[number_of_times_each_philosopher_must_eat]



	memset,
	printf,
	malloc, 
	free, 
	write,

	usleep,
	gettimeofday

	pthread_create,
	pthread_detach,
	pthread_join,
	
	pthread_mutex_init,
	pthread_mutex_destroy,
	pthread_mutex_lock,
	pthread_mutex_unlock



	◦timestamp_in_ms X has taken a fork
	◦timestamp_in_ms X is eating
	◦timestamp_in_ms X is sleeping
	◦timestamp_in_ms X is thinking
	◦timestamp_in_ms X died

	   */