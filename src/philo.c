/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:49 by macassag          #+#    #+#             */
/*   Updated: 2024/03/20 10:11:42 by macassag         ###   ########.fr       */
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
	pthread_mutex_lock(philo->data->lock_eat);
	philo->eat = 0;
	printf("unlock fork");
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->data->lock_eat);
	philo->count_eat++;
	philo->time = philo->time + (philo->info.time_eat);
	philo->last_eat = philo->time;
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
	if (philo->stop)
	{
		
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
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
	while (!philo->stop && (philo->count_eat < info.max_eat && info.max_eat > 1))
	{
		print_log(THINK, &philo);
		check_eat(data);
		if (ft_fork(&philo) == -1)
			return (NULL);
		if (ft_eat_n_sleep(&philo) == -1)
			return (NULL);
	}
	return (NULL);
}

static void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(philo->data->lock_start);
	pthread_mutex_unlock(philo->data->lock_start);
	if (philo->index % 2 == 0)
		usleep(10);
	philo->start_time = get_current_time();
	philo->time = get_time(philo);
	ft_think(&philo);
	return (NULL);
}

void	ft_philo(t_philo *philo)
{
	t_philo	*tmp;
	size_t	i;

	tmp = philo;
	pthread_mutex_lock(philo->data->lock_start);
	while (!tmp->thread)
	{
		pthread_create(&tmp->thread, NULL, routine, tmp);
		tmp = tmp->next;
	}
	pthread_mutex_unlock(philo->data->lock_start);
	tmp = philo;
	i = 0;
	while (i < philo->info.phi_nbr)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
		i++;
	}
	printf("end\n");
	pthread_mutex_destroy(philo->data->lock_print);
	pthread_mutex_destroy(philo->data->lock_start);
	free_lst(&philo);
}
