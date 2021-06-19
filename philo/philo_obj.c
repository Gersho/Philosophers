/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 17:23:09 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/19 13:40:40 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	choose_forks(t_philo *philo)
{
	if (philo->id == 1)
	{
		philo->fork_l = philo->args->philo_count - 1;
		philo->fork_r = 0;
	}
	else
	{
		philo->fork_l = philo->id - 2;
		philo->fork_r = philo->id - 1;
	}
}

int	philo_loop(t_philo *philo)
{
	int	now;

	now = get_elapsed_time(philo->args->start);
	if (now == -1)
		return (-1);
	philo_isalive(philo, now);
	if (philo->args->all_alive == 0)
		return (0);
	if (philo->status == eating)
	{
		if (now >= philo->last_meal + philo->args->time_eat)
			philo_endmeal(philo, now);
	}
	else if (philo->status == sleeping)
	{
		if (now >= philo->sleep_start + philo->args->time_sleep)
		{
			philo->status = thinking;
			philo_output(philo);
		}	
	}
	else if (philo->status == thinking)
		philo_startmeal(philo, now);
	return (0);
}

void	*philo_birth(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->status = thinking;
	philo->last_meal = 0;
	philo->meal_count = 0;
	philo->sleep_start = 0;
	choose_forks(philo);
	while (philo->args->all_alive == 1)
	{
		philo_loop(philo);
		usleep(1);
	}
	free(data);
	return (NULL);
}

int	setup_philos(t_args *args)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < args->philo_count)
	{
		philo = malloc(sizeof(t_philo));
		philo->id = i + 1;
		philo->args = args;
		args->philo_data[i] = philo;
		pthread_create(&args->philos[i], NULL, philo_birth, philo);
		usleep(100);
		i++;
	}
	return (0);
}

int	unspawn_philos(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_count)
	{
		if (pthread_detach(args->philos[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}
