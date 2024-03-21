/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:56 by macassag          #+#    #+#             */
/*   Updated: 2024/03/21 16:26:02 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_death(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	pthread_mutex_lock(&philo->data->lock_data);
	if (philo->data->death)
	{
		pthread_mutex_unlock(&philo->data->lock_data);
		return ;
	}
	printf(DEATH, philo->time, philo->index);
	philo->data->death = 1;
	pthread_mutex_unlock(&philo->data->lock_data);
	philo->stop = 1;
}

void	print_log(char *msg, t_philo **data)
{
	t_philo 		*philo;

	philo = *data;
	check_data(data);
	pthread_mutex_lock(&philo->data->lock_print);
	// pthread_mutex_lock(&philo->data->lock_data);
	philo->life_time = (philo->time - philo->last_eat);
	// if (philo->data->death || philo->data->error)
	// {
	// 	philo->stop = 1;
	// 	return ;
	// }
	// pthread_mutex_unlock(&philo->data->lock_data);
	if (philo->stop == 1)
		;
	else if (philo->life_time > philo->info.time_die)
		ft_death(data);
	else
		printf(msg, philo->time, philo->index);
	pthread_mutex_unlock(&philo->data->lock_print);
}
