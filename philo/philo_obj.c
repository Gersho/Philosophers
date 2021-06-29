/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 17:23:09 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/29 14:01:40 by kzennoun         ###   ########lyon.fr   */
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

int	philo_checkstatus(t_philo *philo, int now)
{
	if (philo->status == eating)
	{
		if (now >= philo->last_meal + philo->args->time_eat)
			if (philo_endmeal(philo, now) == -1)
				return (-1);
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
		if (philo_startmeal(philo, now) == -1)
			return (-1);
	return (0);
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
	philo_checkstatus(philo, now);
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
		if (philo_loop(philo) == -1)
			philo->args->all_alive = 0;
		usleep(75);
	}
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
		if (!philo)
			return (-1);
		philo->id = i + 1;
		philo->args = args;
		args->philo_data[i] = philo;
		if (pthread_create(&args->philos[i], NULL, philo_birth, philo) != 0)
			return (-1);
		usleep(10);
		i++;
	}
	return (0);
}
