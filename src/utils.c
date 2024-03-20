/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:49:52 by macassag          #+#    #+#             */
/*   Updated: 2024/03/20 09:46:52 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_data(t_philo **data)
{
	t_philo *philo;

	philo = *data;
	philo->time = get_time(philo);
	philo->life_time = (philo->time - philo->last_eat);
	pthread_mutex_lock(philo->data->lock_data);
	if (philo->life_time > philo->info.time_die)
		print_log(NULL, data);
	if (philo->data->death || philo->data->error || philo->time)
		philo->stop = 1;
	pthread_mutex_unlock(philo->data->lock_data);
}

void	check_eat(t_philo **data)
{
	t_philo	*philo;
	philo = *data;
	while (1)
	{
		check_data(data);
		if (philo->stop)
			return ;
		pthread_mutex_lock(philo->data->lock_eat);
		if (!philo->next->eat
			&& philo->index % 2 != 0 && philo->info.phi_nbr % 2 == 0)  // l fork
			break;
		else if (!philo->prev->eat) // r fork
			break;
		pthread_mutex_unlock(philo->data->lock_eat);
	}
	philo->eat = 1;
	pthread_mutex_unlock(philo->data->lock_eat);
}

void	take_lfork(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	while (1)
	{
		check_data(data);
		if (philo->stop)
			return ;
		pthread_mutex_lock(philo->data->lock_eat);
		if (!philo->prev->eat)
		{
			pthread_mutex_lock(philo->l_fork);
			philo->time = get_time(philo);
			print_log(FORK, &philo);
			break;
		}
		pthread_mutex_unlock(philo->data->lock_eat);
	}
	pthread_mutex_unlock(philo->data->lock_eat);
}

void	take_rfork(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	while (1)
	{
		check_data(data);
		if (philo->stop)
			return ;
		pthread_mutex_lock(philo->data->lock_eat);
		if (!philo->next->eat)
		{
			pthread_mutex_lock(philo->r_fork);
			philo->time = get_time(philo);
			print_log(FORK, &philo);
			break;
		}
		pthread_mutex_unlock(philo->data->lock_eat);
	}
	pthread_mutex_unlock(philo->data->lock_eat);
}


size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	get_time(t_philo *philo)
{
	size_t	time;

	time = get_current_time();
	philo->time = time - philo->start_time;
	return (philo->time);
}
