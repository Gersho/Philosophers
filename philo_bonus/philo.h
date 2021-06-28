/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:02:53 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/28 11:59:58 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>
# include <semaphore.h>

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
	int				id;
	int				last_meal;
	int				sleep_start;
	int				meal_count;
	t_state			status;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				meal_needed;
	sem_t			*sem_output;
	sem_t			*sem_forks;
	struct timeval	start;
}	t_philo;

typedef struct s_args
{
	int				philo_count;
	int				philo_full;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				meal_count;
	struct timeval	start;
	int				*child_pid;
	int				is_main;
	pthread_t		monitoring;
	int				philo_id;
	t_philo			*philo;
	sem_t			*sem_output;
	sem_t			*sem_forks;
}				t_args;

void	argerror_exit(void);
void	args_init(t_args *args);
int		args_parse(int ac, char **av, t_args *args);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		args_check(t_args *args);
int		get_elapsed_time(struct timeval start);

int		spawn_processes(t_args *args);
int		philo_birth(t_args *args);
int		philo_output(t_philo *philo);
int		philo_startmeal(t_philo *philo, int now);
int		philo_endmeal(t_philo *philo, int now);
int		philo_loop(t_philo *philo);
void	philo_isalive(t_philo *philo, int now);
void	*philo_monitor(void *data);
void	philo_init(t_args *args, t_philo *philo);
#endif