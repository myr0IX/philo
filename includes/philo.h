/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:58:34 by macassag          #+#    #+#             */
/*   Updated: 2024/03/06 14:08:29 by macassag         ###   ########.fr       */
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

# define DEATH "A philo is dead !"

typedef struct s_data
{
	int				death;
	pthread_mutex_t	mutex;
}					t_data;

// typedef struct s_test
// {
// 	t_ft	ft_print;
// }					t_test;

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
	t_data			ft_print;
	t_info			infos;
	size_t			nbr_eat;
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