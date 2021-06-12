/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 17:23:09 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/12 14:00:33 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_birth(void *data)
{
	// int i;
	t_philo philo;
	
	philo = *(t_philo*)data;
	// i = *(int*)data;
	// printf("Philo %d is born\n", i);
	// free(data);
	printf("Philo %d is born\n", philo.id);
	//printf("time death %d\n",philo.args->time_death);

	
	return NULL;
}


int setup_philos(t_args *args, pthread_t *philos)
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
		pthread_create(&philos[i], NULL, philo_birth, philo);
		usleep(20);
		i++;
	}
	return (0);
}



    //  int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
    //      void *(*start_routine)(void *), void *arg);