/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:58:34 by macassag          #+#    #+#             */
/*   Updated: 2024/03/14 13:41:28 by macassag         ###   ########.fr       */
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

# define ARG_ERROR		"Bad arguments !\n"
# define ARG_ERROR2		"./philo\tnumber_of_philosophers\t"
# define ARG_ERROR3		"time_to_die time_to_eat\ttime_to_sleep\t"
# define ARG_ERROR4		"[number_of_times_each_philosopher_must_eat]\n"

# define EAT			"%li %i is eating\n"
# define THINK			"%li %i is thinking\n"
# define SLEEP			"%li %i is sleeping\n"
# define FORK			"%li %i has taken a fork\n"
# define DEATH			"%li %i died\n"

// # define TIME_OUT		time.tv_usec - philo->last_eat.tv_usec

typedef struct s_data
{
	int			death;
	int			start;
}				t_data;

typedef struct s_info
{
	size_t			max_eat;
	size_t			phi_nbr;
	long int		time_die;
	long int		time_sleep;
	long int		time_eat;
	pthread_mutex_t	mutex;
}					t_info;

typedef struct s_philo
{
	int				index;
	long int		time;
	long int	start_time;
	long int		last_eat;
	int				print;
	size_t			count_eat;
	size_t			count_print;
	struct s_philo	*prev;
	struct s_philo	*next;
	t_data			*data;
	t_info			info;
	pthread_t		thread;
	pthread_mutex_t	phi_lock;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_next;
	// pthread_mutex_t	*print_lock;
}					t_philo;

int			ft_atoi(const char *nptr);
void		init_philo(t_info infos);
void		ft_philo(t_philo *philo);
void		free_lst(t_philo **list);
void		error_lst(t_philo **list, char *msg);
void		ft_death(t_philo **list);
void		philo_end(t_philo **list);
int			print_log(char *msg, t_philo **data);
long int	get_time(t_philo *philo);
int			find_less(t_philo *philo);

#endif