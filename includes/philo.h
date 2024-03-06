/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:58:34 by macassag          #+#    #+#             */
/*   Updated: 2024/03/06 15:01:37 by macassag         ###   ########.fr       */
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

typedef struct s_data
{
	int				death;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_2;
}					t_data;

typedef struct s_info
{
	size_t	eat_nbr;
	size_t	phi_nbr;
	size_t	time_die;
	size_t	time_sleep;
	size_t	time_eat;
	t_data	ft_print;
}			t_info;

typedef struct s_philo
{
	int				index;
	int				eat;
	int				sleep;
	t_data			data;
	t_info			infos;
	size_t			nbr_eat;
	size_t			wait_list;
	pthread_t		thread;
	struct timeval	last_eat;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

int		ft_atoi(const char *nptr);
void	init_philo(t_info infos);
void	philo(t_philo *philos);
void	free_lst(t_philo **list);
void	error_lst(t_philo **list, char *msg);
void	ft_death(t_philo **list);
void	philo_end(t_philo **list);

#endif