/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:49:52 by macassag          #+#    #+#             */
/*   Updated: 2024/03/23 15:49:42 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_lfork(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	while (1)
	{
		// if (get_bool(&philo->l_fork->lock_fork, philo->l_fork->fork) == false)
		pthread_mutex_lock(&philo->l_fork->lock_fork);
		if (philo->l_fork->fork)
			break;
		pthread_mutex_unlock(&philo->l_fork->lock_fork);
		if (get_bool(&philo->mutex, philo->stop))
			return ;
	}
	philo->l_fork->fork = false;
	pthread_mutex_unlock(&philo->l_fork->lock_fork);
	// set_fork_bool(philo->l_fork);
	print_log(FORK, &philo);
}

void	take_rfork(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	while (1)
	{
		pthread_mutex_lock(&philo->r_fork->lock_fork);
		// if (get_bool(&philo->r_fork->lock_fork, philo->r_fork->fork))
		if (philo->r_fork->fork)
			break;
		pthread_mutex_unlock(&philo->r_fork->lock_fork);
		if (get_bool(&philo->mutex, philo->stop))
			return ;
	}
	philo->r_fork->fork = false;
	pthread_mutex_unlock(&philo->r_fork->lock_fork);
	// set_fork_bool(philo->r_fork);
	print_log(FORK, &philo);
}
