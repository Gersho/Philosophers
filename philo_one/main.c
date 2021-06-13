/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:05:15 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/13 15:44:56 by kzennoun         ###   ########lyon.fr   */
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

static int	error_ret(void)
{
	write(1, "Error\n", 6);
	return (-1);
}

int	main(int ac, char **av)
{
	t_args	*args;

	if (ac != 5 && ac != 6)
		return error_ret();
	args = malloc(sizeof(t_args));
	if (!args)
		return (-1);
	args_init(args);
	if (args_parse(ac, av, args) == -1)
		return error_ret();
	print_args(args);
	args->philos = malloc(sizeof(pthread_t) * args->philo_count);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->philo_count);
	if(!args->philos || !args->forks)
		return (-1);
	gettimeofday(&args->start, NULL);
	mutex_init(args);
	setup_philos(args);
	while(args->all_alive == 1)
		usleep(100);

	//kill threads
	//free threads
	//kill mutex
	mutex_destroy(args);
	//free mutex
	//free mallocs




	/*
		------malloc list
	
		args
		philos (malloc des threads)
		forks (malloc des mutex)
		
		-----thread list
		philos (threads)

		-----mutex list
	*/



	return (0);
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

Any change of status of a philosopher must be written as follows 
(with X replaced with the philosopher number and timestamp_in_ms the current timestamp in mil-liseconds)
◦timestamp_in_ms X has taken a fork
◦timestamp_in_ms X is eating
◦timestamp_in_ms X is sleeping
◦timestamp_in_ms X is thinking
◦timestamp_in_ms X died
	   */