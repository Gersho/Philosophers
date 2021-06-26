/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:05:15 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/26 15:58:29 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	shutdown(t_args *args, int exit_code)
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

static int	error_ret(void)
{
	write(1, "Error\n", 6);
	return (-1);
}

void	main_monitoring(t_args *args)
{
	int	i;
	int	status;
	int exret;

	while (1)
	{
		i = 0;
		while (i < args->philo_count)
		{
			if (args->child_pid[i] != -1)
			{
				if (waitpid(args->child_pid[i], &status, 0) != -1)
				{
					if (WIFEXITED(status)) 
					{
						exret = WEXITSTATUS(status);
						if (exret == 1)
							shutdown(args, 0);
						else if (exret == 2)
						{
							args->child_pid[i] = -1;
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
			i++;
		}
		usleep(1);
	}
}

int	sem_setup(t_args *args)
{
	sem_unlink("/philo_output");
	sem_unlink("/philo_forks");
	args->sem_output = sem_open("/philo_output", O_CREAT, 0644, 1);
	args->sem_forks = sem_open("/philo_forks",O_CREAT, 0644, args->philo_count);

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
	gettimeofday(&(&args)->start, NULL);
	sem_setup(&args);
	print_args(&args);
	args.child_pid = malloc(sizeof(int) * args.philo_count);
	if (spawn_processes(&args) == -1 || !args.child_pid)
		shutdown(&args, -1);
	//printf("time test: %d\n",get_elapsed_time(args.start));
	//printf("test\n");
	if (args.is_main == 1)
		main_monitoring(&args);
	else
		philo_birth(&args);
	// printf("here from %d\n", args.philo.id);
	// sem_wait(args.sem_output);
	// printf("----coucou from %d\n", args.philo.id);
	// sleep(2);
	// sem_post(args.sem_output);
	return (0);
}
