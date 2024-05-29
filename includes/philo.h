/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:58:34 by macassag          #+#    #+#             */
/*   Updated: 2024/05/29 16:10:36 by macassag         ###   ########.fr       */
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
	RUN,
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
	t_time			value;
}	t_mutex;

typedef struct s_philo
{
	int				index;
	pthread_t		thread;
	pthread_t		check_death;
	size_t			eat;
	size_t			max_eat;
	// t_mutex			*start_time;
	t_mutex			*last_eat;
	t_mutex			*mutex;
	t_mutex			*flag;
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

int		mutex_init(pthread_mutex_t mutex);
void	mutex_destroy(pthread_mutex_t *mutex);
int		check_value(t_mutex *structure);
t_time	get_value(t_mutex *mutex);
void	set_value(t_mutex *mutex, t_time value);



/*	UTILS FONCTIONS	*/

size_t	ft_strlen(char *str);
int		ft_atoi(const char *nptr);
t_time	get_time(t_philo *philo, t_time given_time);
t_time	get_current_time(int flag);
void	ft_usleep(size_t time, t_philo *philo);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	stop_philo(t_philo *phi, size_t size);
void	exit_child(t_philo *phi, size_t size);

/*	FREE FONCTIONS	*/

void	ft_free(void *data);
void	free_struct(t_philo *phi, size_t size);

/*	THREAD FONCTIONS	*/
void	ft_philo(t_philo *philo, size_t	size);
void	print_log(char *msg, t_philo *philo);
void	*check_death(void *data);
t_time	run_philo(t_mutex *mutex,t_time start_time);
void	monitor(t_philo *phi, size_t size);

/*	DEBUG	*/

void	test_mutex(t_mutex *mutex);
void	printf_mutex(t_philo *phi, size_t size);
void	printf_thread(t_philo *phi, size_t size);

#endif