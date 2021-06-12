/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 17:23:09 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/12 13:07:43 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_test(void *data)
{
	int i = *(int*)data;
	printf("Philo %d is born\n", i);
	printf("test2: %d\n", i);
	free(data);
	return NULL;
}


int spawn_socrates(t_args *args, pthread_t *philos)
{
	int	i;

	i = 0;
	while(i < args->philo_count)
	{
		int *data = malloc(sizeof(int));
		*data = i;
		pthread_create(&philos[i], NULL, philo_test, data);
		printf("test\n");
		i++;
	}
	return (0);
}



    //  int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
    //      void *(*start_routine)(void *), void *arg);