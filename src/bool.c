/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:15:09 by macassag          #+#    #+#             */
/*   Updated: 2024/05/19 16:33:29 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_value(t_mutex *structure)
{
	int	ret;

	ret = 0;
	// printf("address = %p\n", structure);
	pthread_mutex_lock(&structure->mutex);
	if (structure->use == UNUSED)
	{
		structure->use = USE;
		ret = USE;
	}
	pthread_mutex_unlock(&structure->mutex);
	return (ret);
}

int	get_int(pthread_mutex_t *mutex, void *var)
{
	int	*value;
	int	ret;

	value = (int *) get_value(mutex, var);
	ret = *value;
	return (ret);
}

t_time	get_time_value(pthread_mutex_t *mutex, void *var)
{
	t_time	*value;
	t_time	ret;

	ret = 0;
	value = (t_time *) get_value(mutex, var);
	ret = *value;
	return (ret);
}

void	*get_value(pthread_mutex_t *mutex, void *var)
{
	void	*ret;

	ret = NULL;
	pthread_mutex_lock(mutex);
	ret = var;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_time(pthread_mutex_t *mutex, t_time *var, t_time value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

void	set_value(pthread_mutex_t *mutex, int *var, int value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}
