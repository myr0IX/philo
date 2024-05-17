/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 08:35:54 by macassag          #+#    #+#             */
/*   Updated: 2024/05/17 17:30:13 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *phi, t_info info)
{
	t_time	time;
	t_time	*result;

	time = get_time(phi);
	if (time == SYS_ERR)
		return (SYS_ERR);
	result = (t_time *) get_value(&phi->mutex, &phi->last_eat) + \
		(t_time) info.life_time;
	if (*result > time)
	{
		set_value(&phi->mutex, &phi->flag, DEAD);
		print_log(DEATH, phi);
		return (1);
	}
	return (0);
}

void	monitor(t_philo *phi, size_t size)
{
	size_t	i;
	int		*flag;

	flag = 0;
	while (1)
	{
		i = 0;
		while (i < size)
		{
			if (check_death(&phi[i], phi->info))
				return ;
			flag = (int *) get_value(&phi[i].mutex, &phi[i].flag);
			if (*flag == STOP)
			{
				set_value(&phi[i].mutex, &phi[i].flag, EXIT);
				pthread_join(phi[i].thread, NULL);
			}
			i++;
		}
	}
}
