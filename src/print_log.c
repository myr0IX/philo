/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:56 by macassag          #+#    #+#             */
/*   Updated: 2024/03/07 15:35:27 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_log(int flag, t_philo **data)
{
	t_philo 		*philo;
	struct timeval	time;
	static int		death;

	philo = *data;
	pthread_mutex_lock(&philo->data.mutex);
	if (death != 0)
		return (-1);
	gettimeofday(&time, NULL);
	if ((flag == 0 && death == 0)
		|| TIME_OUT > (long int)philo->infos.time_die)
	{
		philo->data.death = --death;
		ft_death(&philo);
	}
	else if (flag == 1)
		printf(THINK, time.tv_usec, philo->index);
	else if (flag == 2)
		printf(FORK, time.tv_usec, philo->index);
	else if (flag == 3)
		printf(SLEEP, time.tv_usec, philo->index);
	if (flag == 2 && philo->eat == 2)
		printf(EAT, time.tv_usec, philo->index);
	pthread_mutex_unlock(&philo->data.mutex);
	return (0);
}
