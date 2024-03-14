/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:49:52 by macassag          #+#    #+#             */
/*   Updated: 2024/03/14 14:36:16 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo->time =  time.tv_usec - philo->start_time;
	return (philo->time * 1000);
}

int	find_less(t_philo *philo)
{
	long int	tmp;
	int			index;

	index = philo->index;
	tmp = philo->time;
	// pthread_mutex_lock(&philo->next->phi_lock);
	philo = philo->next;
	while (philo->index != index)
	{
		if (philo->time < tmp && philo->print == 1)
		{
			// printf("utils 1\n");
			pthread_mutex_unlock(&philo->next->phi_lock);
			return (0);
		}
		pthread_mutex_unlock(&philo->phi_lock);
		pthread_mutex_lock(&philo->next->phi_lock);
		philo = philo->next;
	}
	// printf("utils 2 index = %i\n", philo->index);
	pthread_mutex_unlock(&philo->phi_lock);
	return (1);
}
