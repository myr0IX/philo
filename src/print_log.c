/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:56 by macassag          #+#    #+#             */
/*   Updated: 2024/05/28 13:38:30 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(char *msg, t_philo *philo)
{
	t_time	time;
	t_time	ret;
	
	ret = get_value(philo->flag);
	if (ret >= STOP && ft_strncmp(msg, DEATH, ft_strlen(msg)) != 0)
		return ;
	pthread_mutex_lock(&philo->print->mutex);
	time = get_time(philo);
	if (time != SYS_ERR)
		printf(msg, time, philo->index);
	pthread_mutex_unlock(&philo->print->mutex);
}
