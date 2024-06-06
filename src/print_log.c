/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:56 by macassag          #+#    #+#             */
/*   Updated: 2024/06/05 13:59:45 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(char *msg, t_philo *philo)
{
	t_time		time;
	static int	death;

	pthread_mutex_lock(&philo->print->mutex);
	time = get_time(philo, 0);
	if (time != SYS_ERR && death != 1)
		printf(msg, time, philo->index);
	if (ft_strncmp(msg, DEATH, ft_strlen(msg)) == 0)
	{
		death = 1;
		usleep(200);
	}
	pthread_mutex_unlock(&philo->print->mutex);
}
