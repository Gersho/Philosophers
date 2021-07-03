/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:05:15 by kzennoun          #+#    #+#             */
/*   Updated: 2021/07/03 14:20:36 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	main_checkexit(t_args *args, int i)
{	
	int	status;
	int	exret;

	waitpid(args->child_pid[i], &status, 0);
	if (waitpid(args->child_pid[i], &status, 0) != -1)
	{
		if (WIFEXITED(status))
		{
			exret = WEXITSTATUS(status);
			if (exret == 1)
				shutdown(args, 0);
			else if (exret == 2)
			{
				args->philo_full++;
				if (args->philo_full == args->philo_count)
					shutdown(args, 0);
			}
			else
				shutdown(args, -1);
		}
	}
	else
		shutdown(args, -1);
}

void	main_monitoring(t_args *args)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < args->philo_count)
		{
			main_checkexit(args, i);
			i++;
		}
		usleep(30);
	}
}

int	sem_setup(t_args *args)
{
	sem_unlink("/philo_output");
	sem_unlink("/philo_forks");
	args->sem_output = sem_open("/philo_output", O_CREAT, 0644, 1);
	args->sem_forks = sem_open("/philo_forks", O_CREAT, 0644, \
	args->philo_count);
	return (0);
}

int	main(int ac, char **av)
{
	t_args	args;

	args.philo_id = -1;
	if (ac != 5 && ac != 6)
		return (error_ret());
	args_init(&args);
	if (args_parse(ac, av, &args) == -1)
		return (error_ret());
	sem_setup(&args);
	gettimeofday(&(&args)->start, NULL);
	args.child_pid = malloc(sizeof(int) * args.philo_count);
	if (!args.child_pid)
		shutdown(&args, -1);
	if (spawn_processes(&args) == -1)
		shutdown(&args, -1);
	if (args.is_main == 1)
		main_monitoring(&args);
	else
		philo_birth(&args);
	return (0);
}
