/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 17:23:09 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/18 16:41:24 by kzennoun         ###   ########lyon.fr   */
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
	// if (now == 800 && philo->id == 1)
	// {
	// 	printf("");
		
	// }

	if (now >= philo->last_meal + philo->args->time_death)
	{
	 	//philo_debug(philo);
		// if (philo->id == 1)
		// {
		// 	printf("in philo is alive death philo %d ptr: %p\n",philo->id , philo);
		// 	philo_debug(philo);
		// }
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
	//printf("%d %d enter philo_startmeal\n", now, philo->id);
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
	//philo_debug(philo);
	//printf("%d philo %d last meal is %d\n", now, philo->id, philo->last_meal);
	return (0);
}

int	philo_endmeal(t_philo *philo, int now)
{
	if (pthread_mutex_unlock(&philo->args->forks[philo->fork_l]) != 0)
		return (-1);
	if (pthread_mutex_unlock(&philo->args->forks[philo->fork_r]) != 0)
		return (-1);
	// pthread_mutex_unlock(&philo->args->forks[philo->fork_l]);
	// pthread_mutex_unlock(&philo->args->forks[philo->fork_r]);
	if (philo->status == dead)
		return (0);
	philo->meal_count++;
	philo->status = sleeping;
	philo->sleep_start = now;
	if (philo->meal_count >= philo->args->meal_count)
	{
		//philo->status = full;
		philo->args->philo_full++;
		//printf("philo_full %d\n", philo->args->philo_full);
	}
	//printf("philo %d start sleep is %d\n", philo->id, philo->sleep_start);
	philo_output(philo);
	return (0);
}

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
		
		//rattacher philo au args
		philo->id = i + 1;
		philo->args = args;
		args->philo_data[i] = philo;
		// if (philo->id == 1)
		// {
		// 	printf("ptr philo %d at birth: %p\n", philo->id, philo);
		// 	printf("ptr philo %d in args: %p\n", args->philo_data[i]->id, args->philo_data[i]);
		// 	printf("in setup_philo\n");
		// 	philo_debug(philo);
		// }
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
