/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:02:53 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/15 18:30:59 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval	t_timeval;

typedef enum e_state
{
	eating,
	sleeping,
	thinking,
	taking_fork,
	dead
}				t_state;

typedef struct s_args
{
	int				philo_count;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				meal_count;
	int				all_alive;
	t_timeval		start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output;
	pthread_t		*philos;
}				t_args;

typedef struct s_philo
{
	int			id;
	int			last_meal;
	int			sleep_start;
	int			meal_count;
	int			fork_l;
	int			fork_r;
	t_state		status;
	t_args		*args;
}	t_philo;

void	argerror_exit(void);
void	args_init(t_args *args);
int		args_parse(int ac, char **av, t_args *args);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		args_check(t_args *args);
int		get_elapsed_time(t_timeval start);
int		setup_philos(t_args *args);
int		mutex_forks(t_args *args);
int		mutex_init(t_args *args);
int		mutex_destroy(t_args *args);
int		unspawn_philos(t_args *args);
// void	print_args(t_args *args); //debug
// void	philo_debug(t_philo *philo); //debug
#endif