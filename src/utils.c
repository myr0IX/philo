/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:49:52 by macassag          #+#    #+#             */
/*   Updated: 2024/03/21 16:07:03 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_data(t_philo **data)
{
	t_philo *philo;

	philo = *data;
	philo->time = get_time(philo);
	philo->life_time = (philo->time - philo->last_eat);
	if (philo->life_time > philo->info.time_die)
		print_log(NULL, data);
	pthread_mutex_lock(&philo->data->lock_data);
	if (philo->data->death || philo->data->error)
		philo->stop = 1;
	pthread_mutex_unlock(&philo->data->lock_data);
}

void	take_lfork(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	while (1)
	{
		pthread_mutex_lock(&philo->l_fork->lock_fork);
		if (philo->l_fork->fork == true)
			break;
		pthread_mutex_unlock(&philo->l_fork->lock_fork);
		philo->time = get_time(philo);
		philo->life_time = (philo->time - philo->last_eat);
		if (philo->life_time > philo->info.time_die)
		{
			ft_death(data);
			return ;
		}
	}
	pthread_mutex_unlock(&philo->l_fork->lock_fork);
	set_bool(philo->l_fork);
	philo->time = get_time(philo);
	print_log(FORK, &philo);
}

void	take_rfork(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	while (1)
	{
		pthread_mutex_lock(&philo->r_fork->lock_fork);
		if (philo->r_fork->fork == true)
			break;
		pthread_mutex_unlock(&philo->r_fork->lock_fork);
		philo->time = get_time(philo);
		philo->life_time = (philo->time - philo->last_eat);
		if (philo->life_time > philo->info.time_die)
		{
			ft_death(data);
			return ;
		}
	}
	pthread_mutex_unlock(&philo->r_fork->lock_fork);
	set_bool(philo->r_fork);
	philo->time = get_time(philo);
	print_log(FORK, &philo);
}


size_t	get_current_time(t_philo **data)
{
	struct timeval	time;
	t_philo			*philo;

	philo = *data;
	if (gettimeofday(&time, NULL) == -1)
	{
		pthread_mutex_lock(&philo->data->lock_data);
		philo->data->error = 1;
		write(2, "gettimeofday() error\n", 22);
		pthread_mutex_unlock(&philo->data->lock_data);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	get_time(t_philo *philo)
{
	size_t	time;

	time = get_current_time(&philo);
	philo->time = time - philo->start_time;
	return (philo->time);
}
