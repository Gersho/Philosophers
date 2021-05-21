/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:16:31 by kzennoun          #+#    #+#             */
/*   Updated: 2021/05/21 16:33:37 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	argerror_exit(void)
{
	write(1, "Error: Invalid argument(s)\n", 28);
	exit(-1);
}

void	error_exit(int err)
{
	perror("Error");
	exit(err);
}