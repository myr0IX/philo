/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:56 by macassag          #+#    #+#             */
/*   Updated: 2024/03/20 13:31:14 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_death(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	if (philo->data->death)
		return ;
	printf(DEATH, philo->time, philo->index);
	philo->data->death = 1;
	philo->stop = 1;
}

void	print_log(char *msg, t_philo **data)
{
	t_philo 		*philo;

	philo = *data;
	mutex_lock(philo->data->lock_data, data);
	mutex_lock(philo->data->lock_print, data);
	philo->life_time = (philo->time - philo->last_eat);
	if (philo->data->death || philo->data->error)
		philo->stop = 1;
	else if (philo->life_time > philo->info.time_die)
		ft_death(data);
	else
		printf(msg, philo->time, philo->index);
	mutex_unlock(philo->data->lock_data, data);
	mutex_unlock(philo->data->lock_print, data);
}
