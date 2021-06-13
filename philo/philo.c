/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 17:23:09 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/13 16:54:36 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_output(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->args->output) != 0)
		return (-1);
	printf("%d %d ",get_elapsed_time(philo->args->start), philo->id);
	if (philo->status == eating)
		printf("is eating\n");
	else if (philo->status == sleeping)
		printf("is sleeping\n");
	else if (philo->status == thinking)
		printf("is thinking\n");
	else if (philo->status == taking_fork)
		printf("has taken a fork\n");
	else if (philo->status == dead)
		printf("died\n");
	if (pthread_mutex_unlock(&philo->args->output) != 0)
		return (-1);
	return (0);
}


int philo_loop(t_philo *philo)
{
	
}


void *philo_birth(void *data)
{
	// int i;
	t_philo philo;
	
	philo = *(t_philo*)data;
	philo.status = thinking;
	
	philo.last_meal = 0;
	philo.meal_count = 0;
	philo.sleep_start = 0;
	//philo_output(&philo);

	//ready call
	//start routine

	// while (philo.args->all_alive == 1)
	// {

	// }

	free(data);
	return NULL;
}

int setup_philos(t_args *args)
{
	int	i;
	t_philo *philo;
	//int *data;

	i = 0;
	while(i < args->philo_count)
	{
		// data = malloc(sizeof(int));
		// *data = i + 1;
		philo = malloc(sizeof(t_philo));
		philo->id = i + 1;
		philo->args = args;
		pthread_create(&args->philos[i], NULL, philo_birth, philo);
		//pthread_join(philos[i], NULL);
		//usleep(1);
		i++;
	}
	return (0);
}



    //  int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
    //      void *(*start_routine)(void *), void *arg);