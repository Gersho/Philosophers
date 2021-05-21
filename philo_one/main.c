/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:05:15 by kzennoun          #+#    #+#             */
/*   Updated: 2021/05/21 17:29:25 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"





#include <stdio.h>
void	print_args(t_args *args)
{
	printf("philo_count:%d\n", args->philo_count);
	printf("time_death:%d\n", args->time_death);
	printf("time_eat:%d\n", args->time_eat);
	printf("time_sleep:%d\n", args->time_sleep);
	printf("meal_count:%d\n", args->meal_count);
}






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
	Documentation

	https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
	https://randu.org/tutorials/threads/
	https://man7.org/linux/man-pages/man7/pthreads.7.html
	https://docs.oracle.com/cd/E19120-01/open.solaris/816-5137/tlib-1/index.html

	http://ccfit.nsu.ru/~fat/pthreads/816-5137.pdf


*/

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