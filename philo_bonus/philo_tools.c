/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 15:30:33 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/29 17:02:49 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	spawn_processes(t_args *args)
{
	int	fret;
	int	i;

	i = 0;
	while (i < args->philo_count)
	{
		fret = fork();
		if (fret == 0)
		{
			free(args->child_pid);
			args->is_main = 0;
			args->philo_id = i + 1;
			break ;
		}
		else if (fret > 0)
		{
			args->is_main = 1;
			args->child_pid[i] = fret;
		}
		else
			return (-1);
		i++;
		usleep(100);
	}
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

void	philo_init(t_args *args, t_philo *philo)
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
}

int	philo_birth(t_args *args)
{
	t_philo	*philo;
	int		ret;

	philo = malloc(sizeof(t_philo));
	philo_init(args, philo);
	pthread_create(&args->monitoring, NULL, philo_monitor, philo);
	while (1)
	{
		ret = philo_loop(philo);
		if (ret == -1)
			exit(-1);
		if (ret == 1)
			exit(1);
		usleep(50);
	}
	exit(0);
}
