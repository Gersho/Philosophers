/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:55:55 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/28 15:04:08 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_forks(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_count)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	mutex_init(t_args *args)
{
	if (mutex_forks(args) == -1)
		return (-1);
	if (pthread_mutex_init(&args->output, NULL) != 0)
		return (-1);
	return (0);
}

int	mutex_destroy(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_count)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&args->output);
	return (0);
}
