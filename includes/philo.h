/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:58:34 by macassag          #+#    #+#             */
/*   Updated: 2024/03/23 15:27:06 by macassag         ###   ########.fr       */
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

# define EAT			"%li %i is eating\n"
# define THINK			"%li %i is thinking\n"
# define SLEEP			"%li %i is sleeping\n"
# define FORK			"%li %i has taken a fork\n"
# define DEATH			"%li %i died\n"

typedef enum e_time
{
	MICRO,
	MILLI,
}		t_time;

typedef struct s_fork
{
	bool			fork;
	pthread_mutex_t	lock_fork;
}			t_fork;

typedef struct s_data
{
	bool			stop;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_start;
	pthread_mutex_t	lock_eat;
	pthread_mutex_t	lock_data;
}				t_data;

typedef struct s_info
{
	size_t	max_eat;
	size_t	phi_nbr;
	size_t	time_die;
	size_t	time_sleep;
	size_t	time_eat;
}					t_info;

typedef struct s_philo
{
	int				index;
	bool			stop;
	size_t			time;
	size_t			start_time;
	size_t			last_eat;
	size_t			life_time;
	int				print;
	size_t			count_eat;
	struct s_philo	*prev;
	struct s_philo	*next;
	t_data			*data;
	t_info			info;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	t_fork			*l_fork;
	t_fork			*r_fork;
}					t_philo;

int			ft_atoi(const char *nptr);
void		init_philo(t_info infos);
void		ft_philo(t_philo *philo);
void		ft_death(t_philo **list);
void		print_log(char *msg, t_philo **data);

size_t		get_time(t_philo *philo);
size_t		get_current_time(int flag);
void		ft_usleep(size_t time, t_philo *philo);

void		check_time(t_philo **data);

void		take_rfork(t_philo **data);
void		take_lfork(t_philo **data);
void		set_fork_bool(t_fork *fork);
bool		get_bool(pthread_mutex_t *mutex, bool info);


void		ft_free(void *data);
void		free_lst(t_philo **list);
void		error_lst(t_philo **list, char *msg);
int			mutex_init(pthread_mutex_t mutex);
t_data		*del_mutex(t_data *data);
void		mutex_destroy(pthread_mutex_t *mutex);

#endif