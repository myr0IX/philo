/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:15:09 by macassag          #+#    #+#             */
/*   Updated: 2024/03/23 14:09:42 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_fork_bool(t_fork *fork)
{
	// t_fork	*fork;

	// fork = *data;
	pthread_mutex_lock(&(fork->lock_fork));
	if (fork->fork == false)
		fork->fork = true;
	else
		fork->fork = false;
	pthread_mutex_unlock(&(fork->lock_fork));
}

bool	get_bool(pthread_mutex_t *mutex, bool info)
{
	bool	r;

	pthread_mutex_lock(mutex);
	r = info;
	pthread_mutex_unlock(mutex);
	return (r);
}
