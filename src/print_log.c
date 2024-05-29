/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:56 by macassag          #+#    #+#             */
/*   Updated: 2024/05/29 15:39:19 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(char *msg, t_philo *philo)
{
	t_time		time;
	t_time		ret;
	static int	death;
	
	ret = get_value(philo->flag);
	if (ret >= STOP)
		return ;
	pthread_mutex_lock(&philo->print->mutex);
	time = get_time(philo, 0);
	if (time != SYS_ERR && death != 1)
		printf(msg, time, philo->index);
	if (ft_strncmp(msg, DEATH, ft_strlen(msg)) == 0)
		death = 1;
	pthread_mutex_unlock(&philo->print->mutex);
}
