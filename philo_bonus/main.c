/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:05:15 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/19 16:21:08 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	error_ret(void)
{
	write(1, "Error\n", 6);
	return (-1);
}

int	main(int ac, char **av)
{
	t_args	args;

	if (ac != 5 && ac != 6)
		return (error_ret());
	args_init(&args);
	if (args_parse(ac, av, &args) == -1)
		return (error_ret());
	gettimeofday(&(&args)->start, NULL);
	print_args(&args);

	args.child_pid = malloc(sizeof(int) * args.philo_count);
	spawn_processes(&args);

	return (0);
}
