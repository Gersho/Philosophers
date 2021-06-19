/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:02:53 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/19 14:01:06 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args	t_args;

typedef enum e_state
{
	eating,
	sleeping,
	thinking,
	taking_fork,
	dead
}				t_state;

typedef struct s_philo
{
	int			id;
	int			last_meal;
	int			sleep_start;
	int			meal_count;
	t_state		status;
	t_args		*args;
}	t_philo;

typedef struct s_args
{
	int				philo_count;
	int				philo_full;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				meal_count;
	int				all_alive;
	struct timeval	start;
	t_philo			**philo_data;
}				t_args;

void	argerror_exit(void);
void	args_init(t_args *args);
int		args_parse(int ac, char **av, t_args *args);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		args_check(t_args *args);
int		get_elapsed_time(struct timeval start);


#endif