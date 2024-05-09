/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:49 by macassag          #+#    #+#             */
/*   Updated: 2024/05/03 13:06:10 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_philo	*philo;
	
	philo = data;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->flag == RUN)
		{
			philo->flag = THINK;
			pthread_mutex_unlock(&philo->mutex);
			break;
		}
		pthread_mutex_unlock(&philo->mutex);
	}
	while (1)
	{
		
	}
		
}

void	wait_eat(t_philo *philo, size_t size)
{
	t_philo	next;
	t_philo	prev;
	size_t	i;

	i = 0;

}

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

void	ft_philo(t_philo *philo, size_t	size)
{
	size_t		i;
	pthread_t	checker;

	i = 0;
	while (i < size)
	{
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
	while (i > 0)
		printf(THINK, 0L, (int)i--);
	pthread_create(&checker, NULL, checker_phi, philo);
	while (i < size)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(checker, NULL);
	while (i >= 0)
		mutex_destroy(&philo[i].mutex);
	free(philo);
}
