/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:49 by macassag          #+#    #+#             */
/*   Updated: 2024/03/21 16:25:54 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat_n_sleep(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	philo->time = get_time(philo);
	print_log(EAT, &philo);
	usleep(philo->info.time_eat * 1000);
	set_bool(philo->l_fork);
	set_bool(philo->r_fork);
	philo->count_eat++;
	philo->time = philo->time + (philo->info.time_eat);
	philo->last_eat = philo->time;
	while (philo->info.time_sleep > philo->info.time_die)
	{
		philo->time = get_time(philo);
		philo->life_time = (philo->time - philo->last_eat);
		if (philo->life_time > philo->info.time_die)
		{
			ft_death(data);
			return (-1);
		}
	}
	print_log(SLEEP, &philo);
	usleep(philo->info.time_sleep * 1000);
	philo->time = philo->time + (philo->info.time_sleep);
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
	check_data(data);
	if (philo->stop)
	{
		pthread_mutex_lock(&philo->r_fork->lock_fork);
		philo->l_fork->fork = true;
		philo->r_fork->fork = true;
		pthread_mutex_unlock(&philo->r_fork->lock_fork);
		return (-1);
	}
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
	philo->start_time = get_current_time(&philo);
	philo->time = get_time(philo);
	if (philo->index % 2 == 0)
		usleep((philo->info.time_eat / 2) * 1000);
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
