/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:02:53 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/28 15:02:45 by kzennoun         ###   ########lyon.fr   */
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
	int			fork_l;
	int			fork_r;
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
	pthread_mutex_t	*forks;
	pthread_mutex_t	output;
	pthread_t		*philos;
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
int		setup_philos(t_args *args);
int		philo_startmeal(t_philo *philo, int now);
int		philo_endmeal(t_philo *philo, int now);
int		mutex_forks(t_args *args);
int		philo_output(t_philo *philo);
int		mutex_init(t_args *args);
int		mutex_destroy(t_args *args);
int		unspawn_philos(t_args *args);
void	philo_isalive(t_philo *philo, int now);
void	choose_forks(t_philo *philo);
int		grab_fork(t_philo *philo, int fork);
#endif