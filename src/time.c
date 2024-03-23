/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:05:16 by macassag          #+#    #+#             */
/*   Updated: 2024/03/23 16:36:48 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(int flag)
{
	struct timeval	time;
	// t_philo			*philo;

	// time = (struct timeval){0, 0};
	// philo = *data;
	// memset(&time, 0, sizeof(struct timeval));
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

size_t	get_time(t_philo *philo)
{
	size_t	time;

	time = get_current_time(MILLI);
	philo->time = time - philo->start_time;
	return (philo->time);
}

void	check_time(t_philo **data)
{
	t_philo *philo;

	philo = *data;
	philo->time = get_time(philo);
	philo->life_time = (philo->time - philo->last_eat);
	if (philo->life_time > philo->info.time_die)
		print_log(NULL, data);
}

void	ft_usleep(size_t time, t_philo *philo)
{
	size_t	start;
	size_t	t;
	size_t	s;

	start = get_current_time(MILLI);
	while (get_current_time(MILLI) - start < time)
	{
		// printf("[%li]\n", get_current_time(MICRO) - start);
		if (get_bool(&philo->mutex, philo->stop))
			break;
		usleep(500);
		// if (get_bool(&philo->mutex, philo->stop))
		// s = get_current_time(MICRO) - start;
		// t = time - s;
		// if (t > 10000)
		// 	usleep(t / 2);
		// else
		// 	while (get_current_time(MICRO) - start < time)
		// 		;
	}
}
