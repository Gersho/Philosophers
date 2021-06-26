/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 15:30:33 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/26 16:03:46 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int spawn_processes(t_args *args)
{
	int fret;
	int	i;

	i = 0;
	while (i < args->philo_count)
	{
		fret = fork();
		if (fret == 0)
		{
			args->is_main = 0;
			args->philo_id = i + 1;
			break;
		}
		else if (fret > 0)
		{
			args->is_main = 1;
			args->child_pid[i] = fret;
		}
		else 
			return (-1);
		i++;
	}
	return(0);
}

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
		printf("died\n");
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
	if (philo->meal_count >= philo->meal_needed)
	{
		// pthread_mutex_lock(&philo->args->output);
		// philo->args->philo_full++;
		// pthread_mutex_unlock(&philo->args->output);
		free(philo);
		exit(2);
	}
	philo_output(philo);
	return (0);
}


int	philo_loop(t_philo *philo)
{
	int	now;

	now = get_elapsed_time(philo->start);
	if (now == -1)
		return (-1);
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



void	philo_isalive(t_philo *philo, int now)
{
	if (now >= philo->last_meal + philo->time_death)
	{
		philo->status = dead;
		philo_output(philo);
		free(philo);
		exit(1);
	}
}

void *philo_monitor(void *data)
{
	t_philo	*philo;
	int	now;
	philo = (t_philo *)data;
//	printf("time test: %d\n",get_elapsed_time(philo->start));
	while (1)
	{
		now = get_elapsed_time(philo->start);
		philo_isalive(philo, now);
		usleep(1);
	}
	return (NULL);
}

void philo_init(t_args *args, t_philo *philo)
{
	philo->id = args->philo_id;
	philo->status = thinking;
	philo->last_meal = 0;
	philo->meal_count = 0;
	philo->sleep_start = 0;
	philo->time_death = args->time_death;
	philo->time_eat = args->time_eat;
	philo->time_sleep = args->time_sleep;
	philo->meal_needed = args->meal_count;
	philo->sem_forks = args->sem_forks;
	philo->sem_output = args->sem_output;
	philo->start = args->start;
	//args->philo = philo; 
}

int	philo_birth(t_args *args)
{
	t_philo *philo;
	
	//printf("time test: %d\n",get_elapsed_time(args->start));
	philo = malloc(sizeof(t_philo));
	philo_init(args, philo);
	// printf("time test2: %d\n",get_elapsed_time(args->start));
	// printf("time test3: %d\n",get_elapsed_time(philo->start));
	pthread_create(&args->monitoring, NULL, philo_monitor, philo);
	while (1)
	{
		philo_loop(philo);
		// if (args->philo->status == dead)
		// 	break ;
		usleep(1);
	}
	//free(philo);
	exit(0);
}