/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:56 by macassag          #+#    #+#             */
/*   Updated: 2024/03/15 14:44:34 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_death(t_philo **data)
{
	t_philo	*philo;
	int		death;

	philo = *data;
	if (philo->data->death)
	{
		pthread_mutex_unlock(&philo->info->mutex);
		return ;
	}
	printf(DEATH, philo->time, philo->index);
	death = 1;
	philo->data->death = &death;
	usleep(2000000);
	pthread_mutex_unlock(&philo->info->mutex);
}

int	print_log(char *msg, t_philo **data)
{
	size_t			life_time;
	t_philo 		*philo;

	philo = *data;
	philo->print = 1;
	pthread_mutex_lock(&philo->info->mutex);
	life_time = (philo->time - philo->last_eat);
	if (philo->data->death || philo->data->error)
		return (-1);
	if (life_time > philo->info->time_die)
	{
		ft_death(data);
		return (-1);
	}
	printf(msg, philo->time, philo->index);
	pthread_mutex_unlock(&philo->info->mutex);
	philo->print = 0;
	return (0);
}
