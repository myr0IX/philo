/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:15:09 by macassag          #+#    #+#             */
/*   Updated: 2024/05/17 11:24:58 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_value(t_mutex *structure)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&structure->mutex);
	if (structure->use == UNUSED)
	{
		structure->use = USE;
		ret = 1;
	}
	pthread_mutex_unlock(&structure->mutex);
	return (ret);
}

void	unset_value(t_mutex *structure)
{
	pthread_mutex_lock(&structure->mutex);
	structure->use = UNUSED;
	pthread_mutex_unlock(&structure->mutex);
}

int		get_value(pthread_mutex_t *mutex, int var)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = var;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_value(pthread_mutex_t *mutex, int *var, int value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}
