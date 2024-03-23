/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:49:52 by macassag          #+#    #+#             */
/*   Updated: 2024/03/23 09:29:46 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;
	// t_philo			*philo;

	time = (struct timeval){0, 0};
	// philo = *data;
	// memset(&time, 0, sizeof(struct timeval));
	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	get_time(t_philo *philo)
{
	size_t	time;

	time = get_current_time();
	philo->time = time - philo->start_time;
	return (philo->time);
}

void	check_data(t_philo **data)
{
	t_philo *philo;

	philo = *data;
	philo->time = get_time(philo);
	philo->life_time = (philo->time - philo->last_eat);
	if (philo->life_time > philo->info.time_die)
		print_log(NULL, data);
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
	philo->l_fork->fork = false;
	pthread_mutex_unlock(&philo->l_fork->lock_fork);
	philo->time = get_time(philo);
	check_data(data);
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
	philo->r_fork->fork = false;
	pthread_mutex_unlock(&philo->r_fork->lock_fork);
	philo->time = get_time(philo);
	check_data(data);
	print_log(FORK, &philo);
}

