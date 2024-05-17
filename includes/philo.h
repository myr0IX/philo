/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:58:34 by macassag          #+#    #+#             */
/*   Updated: 2024/05/17 17:56:41 by macassag         ###   ########.fr       */
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

# define ARG_ERROR		"Bad arguments !\n \
\n./philo\tnumber_of_philosophers\t \
time_to_die\ttime_to_eat\ttime_to_sleep\t \
[number_of_times_each_philosopher_must_eat]\n\n"

# define EATING			"%li %i is eating\n"
# define THINKING		"%li %i is thinking\n"
# define SLEEPING		"%li %i is sleeping\n"
# define FORK			"%li %i has taken a fork\n"
# define DEATH			"%li %i died\n"

# define UNUSED			0
# define USE			1
# define SYS_ERR		-1

# define MICRO 0
# define MILLI 1

typedef enum e_flag
{
	PAUSE,
	RUN,
	EAT,
	SLEEP,
	THINK,
	STOP,
	DEAD,
	ERROR,
	EXIT,
}	t_flag;

typedef struct s_info
{
	size_t	max_eat;
	size_t	phi_nbr;
	size_t	life_time;
	size_t	time_sleep;
	size_t	time_eat;
}					t_info;

typedef ssize_t	t_time;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				use;
}	t_mutex;

typedef struct s_philo
{
	int				index;
	int				flag;
	t_time			start_time;
	t_time			last_eat;
	size_t			eat;
	size_t			max_eat;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	t_mutex			*print;
	t_mutex			*fork;
	t_mutex			*next_fork;
	t_info			info;
}					t_philo;

typedef struct s_table
{
	size_t	size;
	size_t	life_time;
	int		flag;
}	t_table;

/*	MUTEX FONCTIONS	*/

int		mutex_init(pthread_mutex_t *mutex);
void	mutex_destroy(pthread_mutex_t *mutex);

/*check if fork is available*/
int		check_value(t_mutex *structure);

/*set fork->use to UNUSED*/
void	unset_value(t_mutex *structure);
void	set_value(pthread_mutex_t *mutex, int *var, int value);
void	*get_value(pthread_mutex_t *mutex, void *var);

/*	UTILS FONCTIONS	*/

int		ft_atoi(const char *nptr);
void	ft_free(void *data);
t_time	get_time(t_philo *philo);
t_time	get_current_time(int flag);
void	ft_usleep(size_t time, t_philo *philo);

/*	THREAD FONCTIONS	*/
void	ft_philo(t_philo *philo, size_t	size);
void	print_log(char *msg, t_philo *philo);

void	monitor(t_philo *phi, size_t size);

#endif