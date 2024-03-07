/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:49 by macassag          #+#    #+#             */
/*   Updated: 2024/03/07 15:20:14 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int ft_sleep(t_philo **data)
{
	t_philo	*philo;
	struct timeval	time;

	philo = *data;
	if (print_log(3, data) == -1)
		return (-1);
	philo->sleep = 1;
	usleep(philo->infos.time_sleep);
	gettimeofday(&time, NULL);
	if (TIME_OUT > (long int)philo->infos.time_die)
		print_log(0, data);
	philo->sleep = 0;
	return (0);
}

static int ft_fork(t_philo **data)
{
	t_philo			*philo;
	struct timeval	time;

	philo = *data;
	pthread_mutex_lock(&philo->fork_next);
	gettimeofday(&time, NULL);
	if (TIME_OUT > (long int)philo->infos.time_die)
		print_log(0, data);
	philo->eat = 2;
	if (print_log(2, data) == -1)
		return (-1);
	if (philo->eat == 2)
	{
	 	usleep(philo->infos.time_eat);
		philo->prev->eat = 0;
		philo->next->eat = 0;
		philo->eat = 0;
		pthread_mutex_unlock(&philo->fork);
		gettimeofday(&philo->last_eat, NULL);
	}
}

static int	ft_eat(t_philo **data)
{
	t_philo			*philo;

	philo = *data;
	philo->eat = 1;
	ft_fork(data);
	philo->nbr_eat++;
	if (philo->nbr_eat == philo->infos.eat_nbr
		&& philo->infos.eat_nbr > 1)
		return (-1);
	gettimeofday(&philo->last_eat, NULL);
	return (ft_sleep(data));
}

static void	*ft_think(void *data)
{
	t_philo	*philo;
	struct timeval	time;

	philo = (t_philo *)data;
	if (print_log(1, &philo) == -1)
		return (NULL);
	while (philo->eat != 0)
		continue;
	pthread_mutex_lock(&philo->fork);
	philo->next->eat = -1;
	philo->prev->eat = -1;
	// printf("%i lock mutex\n", philo->index);
	if (TIME_OUT > (long int)philo->infos.time_die)
		print_log(0, &philo);
	if (print_log(2, &philo) == -1)
		return (NULL);
	if (ft_eat(&philo) == -1)
		return (NULL);
	if (philo->data.death == 0)
		ft_think((void *)philo);
	return (NULL);
}

void	philo(t_philo *philos)
{
	t_philo	*tmp;
	size_t	i;

	tmp = philos;
	while (!tmp->thread)
	{
		gettimeofday(&tmp->last_eat, NULL);
		pthread_create(&tmp->thread, NULL, ft_think, tmp);
		tmp = tmp->next;
		usleep(10);
	}
	tmp = philos;
	i = 0;
	while (i < philos->infos.phi_nbr)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
		i++;
	}
}
