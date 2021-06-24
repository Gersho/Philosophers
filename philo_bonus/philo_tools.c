/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 15:30:33 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/24 13:51:22 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_args *args, int i)
{
	args->philo.id = i + 1;
	args->philo.last_meal = 0;
	args->philo.meal_count = 0;
	args->philo.sleep_start = 0;
	args->philo.status = thinking;
}

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
			philo_init(args, i);
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

int	philo_birth(t_args *args)
{
	(void)args;
	return (0);
}