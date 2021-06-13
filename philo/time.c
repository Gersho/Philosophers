/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:52:31 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/12 15:28:36 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* returns elapsed time since start in ms */

int get_elapsed_time(t_timeval start)
{
	t_timeval now;

    if (gettimeofday(&now, NULL) == -1)
		return (-1);
	return (((now.tv_sec * 1000) + (now.tv_usec / 1000)) - ((start.tv_sec * 1000) + (start.tv_usec / 1000)));
}