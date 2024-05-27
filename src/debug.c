/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:15:01 by macassag          #+#    #+#             */
/*   Updated: 2024/05/19 13:55:26 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test_mutex(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->mutex);
	pthread_mutex_unlock(&mutex->mutex);
	printf("mutex ok\n");
}

void	printf_mutex(t_philo *phi, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		printf("philo %zu : address fork = \t%p\n", i + 1, phi[i].fork);
		printf("philo %zu : address fork next = \t%p\n", i + 1, phi[i].next_fork);
		i++;
	}
}
