/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:49 by macassag          #+#    #+#             */
/*   Updated: 2024/03/23 16:05:24 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat_n_sleep(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	// philo->time = get_time(philo);
	print_log(EAT, &philo);
	philo->last_eat = philo->time;
	ft_usleep((philo->info.time_eat * 1000), philo);
	philo->count_eat++;
	// philo->time = philo->time + (philo->info.time_eat);

	set_fork_bool(philo->l_fork);
	set_fork_bool(philo->r_fork);
	print_log(SLEEP, &philo);
	ft_usleep((philo->info.time_sleep * 1000), philo);
	// philo->time = philo->time + (philo->info.time_sleep);
	return (0);
}

static int ft_fork(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	if (philo->index % 2 != 0 && philo->info.phi_nbr % 2 == 0)
	{
		take_lfork(data);
		take_rfork(data);
	}
	else
	{
		take_rfork(data);
		take_lfork(data);
	}
	check_time(data);
	if (philo->stop)
		return (-1);
	return (0);
}

static void	*ft_think(t_philo **data)
{
	t_philo	*philo;
	t_info	info;

	philo = *data;
	info = philo->info;
	while (!philo->stop)
	{
		if (philo->count_eat != 0)
			print_log(THINK, &philo);
		if (ft_fork(&philo) == -1)
			return (NULL);
		if (ft_eat_n_sleep(&philo) == -1)
			return (NULL);
		if (philo->count_eat == info.max_eat && info.max_eat > 1)
			break;
	}
	return (NULL);
}

static void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->data->lock_start);
	pthread_mutex_unlock(&philo->data->lock_start);
	philo->start_time = get_current_time(MILLI);
	if (philo->index % 2 == 0)
		usleep((philo->info.time_eat / 2) * 1000);
	// philo->time = get_time(philo);
	ft_think(&philo);
	return (NULL);
}

void	ft_philo(t_philo *philo)
{
	t_philo	*tmp;
	size_t	i;

	tmp = philo;
	pthread_mutex_lock(&philo->data->lock_start);
	while (!tmp->thread)
	{
		pthread_create(&tmp->thread, NULL, routine, tmp);
		tmp = tmp->next;
	}
	i = 1;
	while (i <= philo->info.phi_nbr)
		printf(THINK, 0L, (int)i++);
	pthread_mutex_unlock(&philo->data->lock_start);
	tmp = philo;
	i = 0;
	while (i < philo->info.phi_nbr)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
		i++;
	}
	del_mutex(philo->data);
	free_lst(&philo);
}
