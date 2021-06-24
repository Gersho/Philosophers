/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:05:15 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/24 14:40:01 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	shutdown(t_args *args)
{
	int	i;


	// i = 0;
	// while (i < args->philo_count)
	// {
	// 	kill(args->child_pid[i], SIGKILL);
	// 	i++;
	// }
	if (args->is_main == 1)
	{
		free(args->child_pid);
	}
	exit(0);
}

static int	error_ret(void)
{
	write(1, "Error\n", 6);
	return (-1);
}

int	main_monitoring(t_args *args)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < args->philo_count)
		{
			if (kill(args->child_pid[i], 0) == -1)
			{
				i = 0;
				while (i < args->philo_count)
				{
					kill(args->child_pid[i], SIGKILL);
					i++;
				}
				return (0);
			}
			i++;
		}
		usleep(10);
	}
	return (0);
}

int	sem_setup(t_args *args)
{
	//destroy les sem existant du meme nom
	sem_unlink("/philo_output");
	sem_unlink("/philo_forks");
	args->sem_output = sem_open("/philo_output", O_CREAT, 0644, 1);
	args->sem_forks = sem_open("/philo_forks",O_CREAT, 0644, args->philo_count);

	return (0);
}

int	main(int ac, char **av)
{
	t_args	args;

	args.philo.id = -1;
	if (ac != 5 && ac != 6)
		return (error_ret());
	args_init(&args);
	if (args_parse(ac, av, &args) == -1)
		return (error_ret());
	gettimeofday(&(&args)->start, NULL);
	sem_setup(&args);
	print_args(&args);
	args.child_pid = malloc(sizeof(int) * args.philo_count);
	if (spawn_processes(&args) == -1 || !args.child_pid)
		shutdown(&args);
	//printf("test\n");
	// if (args.is_main == 1)
	// 	main_monitoring(&args);
	// else
	// 	philo_birth(&args);

	printf("here from %d\n", args.philo.id);
	sem_wait(args.sem_output);
	printf("----coucou from %d\n", args.philo.id);
	sleep(2);
	sem_post(args.sem_output);

	shutdown(&args);
	return (0);
}
