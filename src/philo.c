/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:49 by macassag          #+#    #+#             */
/*   Updated: 2024/03/15 14:45:37 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat_n_sleep(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	philo->time = get_time(philo);
	if (print_log(EAT, &philo) == -1)
		return (-1);
	usleep(philo->info->time_eat * 1000);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->fork_next);
	philo->count_eat++;
	philo->time = philo->time + (philo->info->time_eat);
	philo->last_eat = philo->time;
	if (print_log(SLEEP, &philo) == -1)
		return (-1);
	usleep(philo->info->time_sleep * 1000);
	philo->time = philo->time + (philo->info->time_sleep);
	// philo->time = get_time(philo);
	return (0);
}

static int ft_fork(t_philo **data)
{
	t_philo			*philo;

	philo = *data;
	if (philo->index % 2 != 0 && philo->info->phi_nbr % 2 == 0)
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
	t_info	*info;

	philo = *data;
	info = philo->info;
	while (!philo->data->death && !philo->data->error)
	{
		if (print_log(THINK, &philo) == -1)
			return (NULL);
		if (ft_fork(&philo) == -1)
			return (NULL);
		if (ft_eat_n_sleep(&philo) == -1)
			return (NULL);
		if (philo->count_eat == info->max_eat
			&& info->max_eat > 1)
			return (NULL);
	}
	return (NULL);
}

static void	*routine(void *data)
{
	t_philo	*philo;
	t_info	info;
	t_philo	*tmp;

	philo = (t_philo *)data;
	while (!philo->data->start)
		continue;
	if (philo->index % 2 == 0)
		usleep(10);
	philo->start_time = get_current_time();
	philo->time = get_time(philo);
	ft_think(&philo);
	return (NULL);
}

void	ft_philo(t_philo *philo)
{
	t_philo			*tmp;
	size_t			i;
	int				start;

	tmp = philo;
	while (!tmp->thread)
	{
		pthread_create(&tmp->thread, NULL, routine, tmp);
		tmp = tmp->next;
	}
	start = 1;
	philo->data->start = &start;
	tmp = philo;
	i = 0;
	while (i < philo->info->phi_nbr)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
		i++;
	}
	// free(philo->data);
	pthread_mutex_destroy(&philo->info->mutex);
	free_lst(&philo);
}
