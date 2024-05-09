/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:58:34 by macassag          #+#    #+#             */
/*   Updated: 2024/05/03 13:01:27 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

# define ARG_ERROR		"Bad arguments !\n"
# define ARG_ERROR2		"\n./philo\t\tnumber_of_philosophers\t\t"
# define ARG_ERROR3		"time_to_die\ttime_to_eat\ttime_to_sleep\t"
# define ARG_ERROR4		"[number_of_times_each_philosopher_must_eat]\n\n"

# define EATING			"%li %i is eating\n"
# define THINKING		"%li %i is thinking\n"
# define SLEEPING		"%li %i is sleeping\n"
# define FORK			"%li %i has taken a fork\n"
# define DEATH			"%li %i died\n"

typedef enum e_time
{
	MICRO,
	MILLI,
}		t_time;

typedef enum e_flag
{
	PAUSE,
	RUN,
	STOP,
	EAT,
	SLEEP,
	THINK,
	DEAD,
}	t_flag;

typedef struct s_info
{
	size_t	max_eat;
	size_t	phi_nbr;
	size_t	life_time;
	size_t	time_sleep;
	size_t	time_eat;
}					t_info;

typedef struct s_philo
{
	int				index;
	int				flag;
	int				eat;
	size_t			start_time;
	size_t			last_eat;
	size_t			count_eat;
	size_t			max_eat;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*lock_print;
	t_info			info;
	struct s_philo	next;
	struct s_philo	prev;
}					t_philo;

int			ft_atoi(const char *nptr);
void		init_philo(t_info infos);
void		ft_philo(t_philo *philo, size_t	size);
void		print_log(char *msg, t_philo *philo);

size_t		get_time(t_philo philo);
size_t		get_current_time(int flag);
void		ft_usleep(size_t time, t_philo *philo);

void		check_time(t_philo **data);

void		ft_free(void *data);
int			mutex_init(pthread_mutex_t mutex);
void		mutex_destroy(pthread_mutex_t *mutex);

#endif