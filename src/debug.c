/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:15:01 by macassag          #+#    #+#             */
/*   Updated: 2024/05/28 10:29:44 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test_mutex(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->mutex);
	pthread_mutex_unlock(&mutex->mutex);
	printf("mutex ok\n");
}

void	printf_thread(t_philo *phi, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		printf("philo %zu : thread = \t%lu\n", i + 1, phi[i].thread);
		i++;
	}
	write(1, "\n", 1);
}

void	printf_mutex(t_philo *phi, size_t size)
{
	size_t	i;

	i = 0;
	printf("philo address : pointer = \t%p\n", phi);
	while (i < size)
	{
		printf("philo %zu : mutex = \t\t%p\n", i + 1, phi[i].mutex);
		printf("philo %zu : address fork = \t%p\n", i + 1, phi[i].fork);
		printf("philo %zu : address fork next = \t%p\n", i + 1, phi[i].next_fork);
		i++;
	}
	write(1, "\n", 1);
}
