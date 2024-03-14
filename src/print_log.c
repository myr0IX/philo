/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:56 by macassag          #+#    #+#             */
/*   Updated: 2024/03/14 14:39:23 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_log(char *msg, t_philo **data)
{
	size_t			life_time;
	t_philo 		*philo;
	// struct timeval	time;
	// pthread_mutex_t	*mutex;

	philo = *data;
	philo->print = 1;
	pthread_mutex_lock(&philo->info.mutex);
	life_time = (philo->time - philo->last_eat);
	if (philo->data->death)
		return (-1);
	if (life_time > philo->info.time_die)
	{
		ft_death(data);
		return (-1);
	}
	printf(msg, philo->time / 1000, philo->index);
	pthread_mutex_unlock(&philo->info.mutex);
	philo->print = 0;
	return (0);
}
