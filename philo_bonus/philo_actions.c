/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:27:56 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/29 15:11:19 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_output(t_philo *philo)
{
	sem_wait(philo->sem_output);
	printf("%d %d ", get_elapsed_time(philo->start), philo->id);
	if (philo->status == eating)
		printf("is eating\n");
	else if (philo->status == sleeping)
		printf("is sleeping\n");
	else if (philo->status == thinking)
		printf("is thinking\n");
	else if (philo->status == dead)
	{
		printf("died\n");
		return (0);
	}
	else if (philo->status == taking_fork)
		printf("has taken a fork\n");
	sem_post(philo->sem_output);
	return (0);
}

int	philo_startmeal(t_philo *philo, int now)
{
	sem_wait(philo->sem_forks);
	philo->status = taking_fork;
	philo_output(philo);
	sem_wait(philo->sem_forks);
	philo->status = taking_fork;
	philo_output(philo);
	now = get_elapsed_time(philo->start);
	philo_isalive(philo, now);
	if (philo->status == dead)
		philo_endmeal(philo, now);
	else
		philo->status = eating;
	philo_output(philo);
	philo->last_meal = now;
	return (0);
}

int	philo_endmeal(t_philo *philo, int now)
{
	sem_post(philo->sem_forks);
	sem_post(philo->sem_forks);
	if (philo->status == dead)
		return (0);
	philo->meal_count++;
	philo->status = sleeping;
	philo->sleep_start = now;
	if (philo->meal_needed != -1 && philo->meal_count >= philo->meal_needed)
	{
		free(philo);
		exit(2);
	}
	philo_output(philo);
	return (0);
}

void	*philo_monitor(void *data)
{
	t_philo	*philo;
	int		now;

	philo = (t_philo *)data;
	while (1)
	{
		now = get_elapsed_time(philo->start);
		philo_isalive(philo, now);
		usleep(50);
	}
	return (NULL);
}

int	philo_loop(t_philo *philo)
{
	int	now;

	now = get_elapsed_time(philo->start);
	if (now == -1)
		return (-1);
	if (philo->status == dead)
		return (1);
	if (philo->status == eating)
	{
		if (now >= philo->last_meal + philo->time_eat)
			philo_endmeal(philo, now);
	}
	else if (philo->status == sleeping)
	{
		if (now >= philo->sleep_start + philo->time_sleep)
		{
			philo->status = thinking;
			philo_output(philo);
		}	
	}
	else if (philo->status == thinking)
		philo_startmeal(philo, now);
	return (0);
}
