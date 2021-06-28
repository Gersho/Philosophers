/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 12:09:42 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/28 12:10:47 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	shutdown(t_args *args, int exit_code)
{
	int	i;

	if (args->is_main == 1)
	{
		sem_close(args->sem_forks);
		sem_close(args->sem_output);
		sem_unlink("/philo_output");
		sem_unlink("/philo_forks");
		i = 0;
		while (i < args->philo_count)
		{
			if (args->child_pid[i] != -1)
				kill(args->child_pid[i], SIGKILL);
			i++;
		}
		free(args->child_pid);
	}
	exit(exit_code);
}

int	error_ret(void)
{
	write(1, "Error\n", 6);
	return (-1);
}
