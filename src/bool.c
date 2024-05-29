/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:15:09 by macassag          #+#    #+#             */
/*   Updated: 2024/05/29 11:16:04 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*check if fork is available*/
int	check_value(t_mutex *structure)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&structure->mutex);
	if (structure->value == UNUSED)
	{
		structure->value = USE;
		ret = USE;
	}
	pthread_mutex_unlock(&structure->mutex);
	return (ret);
}

// get the value of the mutex
t_time	get_value(t_mutex *mutex)
{
	t_time	ret;

	pthread_mutex_lock(&mutex->mutex);
	ret = mutex->value;
	pthread_mutex_unlock(&mutex->mutex);
	return (ret);
}

// set the value of the mutex
void	set_value(t_mutex *mutex, t_time value)
{
	pthread_mutex_lock(&mutex->mutex);
	mutex->value = value;
	pthread_mutex_unlock(&mutex->mutex);
}
