/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:56 by macassag          #+#    #+#             */
/*   Updated: 2024/05/17 11:40:58 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(char *msg, t_philo *philo)
{
	t_philo	*philo;
	t_time	time;

	time = get_time(philo);
	pthread_mutex_lock(&philo->print->mutex);
	if (!time == SYS_ERR)
		printf(msg, time, philo->index);
	pthread_mutex_unlock(&philo->print->mutex);
}
