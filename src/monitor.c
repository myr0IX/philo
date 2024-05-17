/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 08:35:54 by macassag          #+#    #+#             */
/*   Updated: 2024/05/17 09:17:15 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	static int	count;

	pthread_mutex_lock(&philo->mutex);
	if (philo->flag == STOP)
		count++;
	if (count == philo->info.phi_nbr - 1)
		return (1);
	if (get_time(*philo) - philo->last_eat >= philo->info.life_time)
	{
		philo->flag = DEAD;
		print_log(DEATH, &philo);
		pthread_mutex_unlock(&philo->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex);
	return (0);
}

void	monitor(void *data)
{
	t_table	table;
	
	
}

void	*checker_phi(void *data)
{
	t_philo	*philo;
	size_t	size;
	size_t	i;
	int	death;

	philo = data;
	size = philo->info.phi_nbr;
	death = 0;
	i = 0;
	while (i < size)
	{
		pthread_mutex_lock(&philo[i].mutex);
		philo[i].flag = RUN;
		pthread_mutex_unlock(&philo[i++].mutex);
	}
	while (!death)
	{
		i = 0;
		while (i < size)
			death = check_death(&philo[i++]);
	}
	i = 0;
	while (i < size)
	{
		pthread_mutex_lock(&philo[i].mutex);
		philo[i].flag = STOP;
		pthread_mutex_unlock(&philo[i++].mutex);
	}
	
}