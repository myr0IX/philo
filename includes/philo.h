/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:58:34 by macassag          #+#    #+#             */
/*   Updated: 2024/03/15 14:59:22 by macassag         ###   ########.fr       */
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

typedef struct s_data
{
	int			*death;
	int			*start;
	int			*error;
}				t_data;

typedef struct s_info
{
	size_t			max_eat;
	size_t			phi_nbr;
	size_t		time_die;
	size_t		time_sleep;
	size_t		time_eat;
	pthread_mutex_t	mutex;
}					t_info;

typedef struct s_philo
{
	int				index;
	size_t			time;
	size_t			start_time;
	size_t			last_eat;
	int				print;
	size_t			count_eat;
	struct s_philo	*prev;
	struct s_philo	*next;
	t_data			*data;
	t_info			info;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_next;
}					t_philo;

int			ft_atoi(const char *nptr);
void		init_philo(t_info infos);
void		ft_philo(t_philo *philo);
void		free_lst(t_philo **list);
void		error_lst(t_philo **list, char *msg);
void		ft_death(t_philo **list);
void		philo_end(t_philo **list);
int			print_log(char *msg, t_philo **data);
size_t		get_time(t_philo *philo);
size_t		get_current_time(void);

#endif