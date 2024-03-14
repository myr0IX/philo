/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:49 by macassag          #+#    #+#             */
/*   Updated: 2024/03/14 14:36:42 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat(t_philo **data)
{
	t_philo			*philo;
	struct timeval	time;

	philo = *data;
	philo->time = get_time(philo);
	if (print_log(EAT, &philo) == -1)
		return (-1);
	// gettimeofday(&time, NULL);
	usleep(philo->info.time_eat - (time.tv_usec - philo->time));
	philo->time = philo->time + philo->info.time_eat;
	// gettimeofday(&time, NULL);
	philo->last_eat = philo->time;
	if (print_log(SLEEP, &philo) == -1)
		return (-1);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->fork_next);
	philo->count_eat++;
	usleep(philo->info.time_sleep - (time.tv_usec - philo->time));
	return (0);
}

static int ft_fork(t_philo **data)
{
	t_philo			*philo;
	struct timeval	time;

	philo = *data;
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		philo->time = get_time(philo);
		if (print_log(FORK, &philo) == -1)
			return (-1);
		pthread_mutex_lock(philo->fork_next);
		philo->time = get_time(philo);
		if (print_log(FORK, &philo) == -1)
			return (-1);
	}
	else
	{
		pthread_mutex_lock(philo->fork_next);
		philo->time = get_time(philo);
		if (print_log(FORK, &philo) == -1)
			return (-1);
		pthread_mutex_lock(&philo->fork);
		philo->time = get_time(philo);
		if (print_log(FORK, &philo) == -1)
			return (-1);
	}
	return (0);
}

static void	*ft_think(t_philo **data)
{
	t_philo	*philo;
	t_info	info;
	struct timeval	time;

	philo = *data;
	info = philo->info;
	while (1)
	{
		gettimeofday(&time, NULL);
		philo->time = time.tv_usec - philo->start_time;
		if (print_log(THINK, &philo) == -1)
			return (NULL);
		if (ft_fork(&philo) == -1)
			return (NULL);
		if (ft_eat(&philo) == -1)
			return (NULL);
		if (philo->count_eat <= info.max_eat
			&& info.max_eat > 1)
			return (NULL);
	}
	return (NULL);
}

static void	*routine(void *data)
{
	t_philo	*philo;
	t_info	info;
	t_philo	*tmp;
	struct timeval	time;

	philo = (t_philo *)data;
	while (!philo->data->start)
		continue;
	gettimeofday(&time, NULL);
	philo->start_time = time.tv_usec;
	ft_think(&philo);
	return (NULL);
}

void	ft_philo(t_philo *philo)
{
	t_philo			*tmp;
	size_t			i;
	struct timeval	time;

	tmp = philo;
	// gettimeofday(&time, NULL);
	while (!tmp->thread)
	{
		// gettimeofday(&tmp->last_eat, NULL);
		pthread_create(&tmp->thread, NULL, routine, tmp);
		tmp = tmp->next;
	}
	philo->data->start = 1;
	tmp = philo;
	i = 0;
	while (i < philo->info.phi_nbr)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
		i++;
	}
	free(philo->data);
	pthread_mutex_destroy(&philo->info.mutex);
	free_lst(&philo);
}
