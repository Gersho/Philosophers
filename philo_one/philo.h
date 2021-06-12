/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:02:53 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/11 17:28:37 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval t_timeval;

// typedef struct s_time
// {
// 	t_timeval	*tval;
// 	int			t_ms;
// }				t_time;

typedef struct s_args
{
	int			philo_count;
	int			time_death;
	int			time_eat;
	int			time_sleep;
	int			meal_count;
	t_timeval	start;
}				t_args;

typedef struct s_philo
{
	int		last_meal;
	int		sleep_start;
}	t_philo;


void	argerror_exit(void);
void	args_init(t_args *args);
int		args_parse(int ac, char **av, t_args *args);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		args_check(t_args *args);
int 	get_elapsed_time(t_args *args);
int spawn_socrates(t_args *args, pthread_t *philos);
#endif