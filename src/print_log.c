/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:56 by macassag          #+#    #+#             */
/*   Updated: 2024/03/13 14:44:37 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_log(char *msg, t_philo **data)
{
	size_t			life_time;
	t_philo 		*philo;
	struct timeval	time;
	pthread_mutex_t	*mutex;

	philo = *data;
	pthread_mutex_lock(&philo->info.mutex);
	gettimeofday(&time, NULL);
	life_time = time.tv_usec - philo->last_eat.tv_usec;
	if (life_time > philo->info.time_die)
		ft_death(data);
	printf(msg, time.tv_sec - philo->data->start_time, philo->index);
	pthread_mutex_unlock(&philo->info.mutex);
	philo->time = time.tv_usec;
	return (0);
}
