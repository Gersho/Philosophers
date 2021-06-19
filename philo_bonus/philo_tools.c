/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 15:30:33 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/19 16:42:48 by kzennoun         ###   ########lyon.fr   */
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
			// in child process
			//free(args->child_pid);
			printf("this is child process #%d\n", i);
			break;
		}
		else
		{

			//in main process
			args->child_pid[i] = fret;
		}

		i++;

	}
	if (fret != 0)
	{
		i = 0;
		while (i < args->philo_count)
		{
			printf("pid #%d : %d\n", i, args->child_pid[i]);
			i++;
		}

	}
	

	return(0);
}