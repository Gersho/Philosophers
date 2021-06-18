/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:05:15 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/18 12:34:00 by kzennoun         ###   ########lyon.fr   */
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
	free(args->philo_data);
	return (0);
}

void main_ptrdebug(t_args *args)
{	
	int i;

	i = 0;
	while (i < args->philo_count)
	{
		// if (args->philo_data[i]->id == 1)
		// {
			philo_debug(args->philo_data[i]);
			printf("in main philo %d ptr: %p\n",i ,args->philo_data[i]);
		// }
		i++;
	}
}

int main_monitoring(t_args *args)
{
	int	now;
	int	i;

	while (args->all_alive == 1)
	{
		i = 0;
		while (i < args->philo_count)
		{
			now = get_elapsed_time(args->start);
			if (now == -1)
				return (-1);
			//printf("in main philo %d ptr: %p\n",i ,args->philo_data[i]);
			//philo_debug(args->philo_data[i]);
			philo_isalive(args->philo_data[i], now);
			i++;
		}
		//break;
		usleep(10);
	}
	return (0);
}


int	main(int ac, char **av)
{
	t_args	*args;
	int		i;

	if (ac != 5 && ac != 6)
		return (error_ret());
	args = malloc(sizeof(t_args));
	if (!args)
		return (-1);
	args_init(args);
	if (args_parse(ac, av, args) == -1)
		return (error_ret());
	//print_args(args);
	args->philos = malloc(sizeof(pthread_t) * args->philo_count);
	args->philo_data = malloc(sizeof(t_philo*) * args->philo_count);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->philo_count);
	if (!args->philos || !args->forks || !args->philo_data)
		return (-1);

	printf("args->philo-data ptr: %p\n", args->philo_data);
	args->debug_plz = 0;


	gettimeofday(&args->start, NULL);
	mutex_init(args);
	setup_philos(args);

	main_ptrdebug(args);

	if ( main_monitoring(args) == -1)
		return (-1);



	shutdown(args);
	return (0);
}
