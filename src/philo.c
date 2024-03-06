/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:49 by macassag          #+#    #+#             */
/*   Updated: 2024/03/06 14:55:14 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_log(int flag, t_philo **data)
{
	t_philo *philo;
	struct timeval	time;
	static int		death;

	philo = *data;
	pthread_mutex_lock(&philo->data.mutex);
	if (death != 0)
		return (-1);
	gettimeofday(&time, NULL);
	if ((flag == 0 && death == 0)
		|| time.tv_usec - philo->last_eat.tv_usec > (long int)philo->infos.time_die)
	{
		philo->data.death = death--;
		ft_death(&philo);
	}
	else if (flag == 1)
		printf("[%li]\tPhilo[%i] is thinking\n", time.tv_usec, philo->index);
	else if (flag == 3)
		printf("[%li]\tPhilo[%i] is sleeping\n", time.tv_usec, philo->index);
	else if (flag == 2)
		printf("[%li]\tPhilo[%i] has taken a fork\n", time.tv_usec, philo->index);
	if (flag == 2 && philo->eat == 2)
		printf("[%li]\tPhilo[%i] is eating\n", time.tv_usec, philo->index);
	pthread_mutex_unlock(&philo->data.mutex);
	return (0);
}

static int ft_sleep(t_philo **philo)
{
	t_philo	*tmp;
	struct timeval	time;

	tmp = *philo;
	if (print_log(3, philo) == -1)
		return (-1);
	tmp->sleep = 1;
	usleep(tmp->infos.time_sleep);
	gettimeofday(&time, NULL);
	if (time.tv_usec - tmp->last_eat.tv_usec > (long int)tmp->infos.time_die)
		print_log(0, philo);
	tmp->sleep = 0;
	return (0);
}

static int	ft_eat(t_philo **philo)
{
	t_philo			*tmp;

	tmp = *philo;

	while (tmp->next->eat == 1 && tmp->prev->eat == 1)
		continue ;
	tmp->eat = 1;
	if (print_log(2, philo) == -1)
		return (-1);
	tmp->eat++;
	if (print_log(2, philo) == -1)
		return (-1);
	usleep(tmp->infos.time_eat); 
	tmp->eat = 0;
	tmp->nbr_eat++;
	if (tmp->nbr_eat == tmp->infos.eat_nbr && tmp->infos.eat_nbr > 1)
		return (-1);
	gettimeofday(&tmp->last_eat, NULL);
	return (ft_sleep(philo));
}

static void	*ft_think(void *data)
{
	t_philo	*philo;
	struct timeval	time;

	philo = (t_philo *)data;
	if (print_log(1, &philo) == -1)
		return (NULL);
	gettimeofday(&time, NULL);
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
