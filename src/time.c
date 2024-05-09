/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:05:16 by macassag          #+#    #+#             */
/*   Updated: 2024/05/03 12:50:18 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(int flag)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (-1);
	}
	if (flag == MILLI)
		return (time.tv_sec * 1000 + time.tv_usec / 1000);
	if (flag == MICRO)
		return (time.tv_sec * 1e6 + time.tv_usec);
}

size_t	get_time(t_philo philo)
{
	size_t	time;

	time = get_current_time(MILLI);
	return (time - philo.start_time);
}

void	ft_usleep(size_t time, t_philo philo)
{
	size_t	start;
	size_t	t;
	size_t	s;

	start = get_current_time(MILLI);
	while (get_current_time(MILLI) - start < time)
	{
		
		pthread_mutex_lock(&philo.mutex);
		if (philo.flag == DEAD || philo.flag == STOP)
		{
			pthread_mutex_unlock(&philo.mutex);
			break;
		}
		pthread_mutex_unlock(&philo.mutex);
		usleep(500);
	}
}
