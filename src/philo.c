/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:49 by macassag          #+#    #+#             */
/*   Updated: 2024/03/13 15:56:04 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat(t_philo **data)
{
	t_philo			*philo;
	struct timeval	time;

	philo = *data;
	print_log(EAT, &philo);
	gettimeofday(&time, NULL);
	usleep(philo->info.time_eat);
	print_log(SLEEP, &philo);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->fork_next);
	philo->eat = 0;
	usleep(philo->info.time_sleep);
	return (0);
}

static int ft_fork(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	while (philo->prev->eat != 0 && philo->next->eat != 0)
		continue;
	philo->eat = 1;
	pthread_mutex_lock(&philo->fork);
	print_log(FORK, &philo);
	pthread_mutex_lock(philo->fork_next);
	print_log(FORK, &philo);
	return (0);
}

static void	*ft_think(void *data)
{
	t_philo	*philo;
	t_info	info;
	t_philo	*tmp;

	philo = (t_philo *)data;
	info = philo->info;
	// while (!info->start_time)
	// 	continue;
	while (1)
	{
		print_log(THINK, &philo);
		ft_fork(&philo);
		ft_eat(&philo);
		if (philo->count_eat <= info.max_eat
			&& info.max_eat > 1)
			return (NULL);
	}
	return (NULL);
}

void	ft_philo(t_philo *philo)
{
	t_philo			*tmp;
	size_t			i;
	struct timeval	time;

	tmp = philo;
	gettimeofday(&time, NULL);
	// data->start_time = time.tv_sec;
	while (!tmp->thread)
	{
		gettimeofday(&tmp->last_eat, NULL);
		pthread_create(&tmp->thread, NULL, ft_think, tmp);
		tmp = tmp->next;
		usleep(10);
	}
	tmp = philo;
	i = 0;
	while (i < philo->info.phi_nbr)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
		i++;
	}
}
