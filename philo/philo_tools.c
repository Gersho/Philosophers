/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:43:26 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/19 12:55:33 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_output(t_philo *philo)
{
	if (philo->args->all_alive == 0)
		return (0);
	if (pthread_mutex_lock(&philo->args->output) != 0)
		return (-1);
	if (philo->args->all_alive == 0)
		return (0);
	printf("%d %d ", get_elapsed_time(philo->args->start), philo->id);
	if (philo->status == eating)
		printf("is eating\n");
	else if (philo->status == sleeping)
		printf("is sleeping\n");
	else if (philo->status == thinking)
		printf("is thinking\n");
	else if (philo->status == dead)
		printf("died\n");
	else if (philo->status == taking_fork)
		printf("has taken a fork\n");
	if (pthread_mutex_unlock(&philo->args->output) != 0)
		return (-1);
	return (0);
}

void	philo_isalive(t_philo *philo, int now)
{
	if (now >= philo->last_meal + philo->args->time_death)
	{
		philo->status = dead;
		philo_output(philo);
		philo->args->all_alive = 0;
	}
}

int	grab_fork(t_philo *philo, int fork)
{
	if (pthread_mutex_lock(&philo->args->forks[fork]) != 0)
		return (-1);
	philo->status = taking_fork;
	philo_output(philo);
	return (0);
}

int	philo_startmeal(t_philo *philo, int now)
{
	if (grab_fork(philo, philo->fork_l) == -1)
		return (-1);
	if (grab_fork(philo, philo->fork_r) == -1)
		return (-1);
	now = get_elapsed_time(philo->args->start);
	philo_isalive(philo, now);
	if (philo->status == dead)
		philo_endmeal(philo, now);
	philo->status = eating;
	philo_output(philo);
	philo->last_meal = now;
	return (0);
}

int	philo_endmeal(t_philo *philo, int now)
{
	if (pthread_mutex_unlock(&philo->args->forks[philo->fork_l]) != 0)
		return (-1);
	if (pthread_mutex_unlock(&philo->args->forks[philo->fork_r]) != 0)
		return (-1);
	if (philo->status == dead)
		return (0);
	philo->meal_count++;
	philo->status = sleeping;
	philo->sleep_start = now;
	if (philo->meal_count >= philo->args->meal_count)
	{
		pthread_mutex_lock(&philo->args->output);
		philo->args->philo_full++;
		pthread_mutex_unlock(&philo->args->output);
	}
	philo_output(philo);
	return (0);
}
