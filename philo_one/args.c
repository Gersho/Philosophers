/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:12:34 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/11 12:49:38 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	args_init(t_args *args)
{
	args->philo_count = -1;
	args->time_death = -1;
	args->time_eat = -1;
	args->time_sleep = -1;
	args->meal_count = -1;
}

static int	obtain_value(char *arg)
{
	int		value;
	char	*ptr;

	value = ft_atoi(arg);
	ptr = ft_itoa(value);
	if (!ptr)
		return (-1);
	if (ft_strncmp(ptr, arg, 50) != 0)
	{
		free(ptr);
		return (-1);
	}
	free(ptr);
	return (value);
}

int	args_parse(int ac, char **av, t_args *args)
{
	args->philo_count = obtain_value(av[1]);
	args->time_death = obtain_value(av[2]);
	args->time_eat = obtain_value(av[3]);
	args->time_sleep = obtain_value(av[4]);
	if (ac == 6)
	{
		if (obtain_value(av[5]) != -1)
			args->meal_count = obtain_value(av[5]);
		else
			return (-1);
	}
	return (args_check(args));
}

int	args_check(t_args *args)
{
	if (args->philo_count < 1 || args->time_death <= 0 || args->time_eat <= 0
		|| args->time_sleep <= 0 || args->meal_count == 0
		|| args->meal_count < -1)
		return (-1);
	return (0);
}
