/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:15:09 by macassag          #+#    #+#             */
/*   Updated: 2024/03/21 16:07:11 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_fork *fork)
{
	// t_fork	*fork;

	// fork = *data;
	pthread_mutex_lock(&fork->lock_fork);
	if (fork->fork == false)
		fork->fork = true;
	else
		fork->fork = false;
	pthread_mutex_unlock(&fork->lock_fork);
}
