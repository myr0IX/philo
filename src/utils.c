/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:49:52 by macassag          #+#    #+#             */
/*   Updated: 2024/03/20 13:31:46 by macassag         ###   ########.fr       */
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
	mutex_lock(philo->data->lock_data, data);
	if (philo->data->death || philo->data->error)
		philo->stop = 1;
	mutex_unlock(philo->data->lock_data, data);
}

void	take_lfork(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	mutex_lock(philo->l_fork, data);
	philo->time = get_time(philo);
	print_log(FORK, &philo);
}

void	take_rfork(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	mutex_lock(philo->r_fork, data);
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
		mutex_lock(philo->data->lock_data, data);
		philo->data->error = 1;
		write(2, "gettimeofday() error\n", 22);
		mutex_unlock(philo->data->lock_data, data);
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
