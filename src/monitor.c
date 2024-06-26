/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 08:35:54 by macassag          #+#    #+#             */
/*   Updated: 2024/06/05 13:53:43 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	if_death(t_philo *phi, t_info info)
{
	t_time	time;
	t_time	result;

	time = 0;
	result = 0;
	time = get_time(phi, 0);
	if (time == SYS_ERR)
		return (SYS_ERR);
	result = get_value(phi->last_eat) + (t_time) info.life_time;
	if (result < time)
		return (DEAD);
	return (0);
}

int	death(t_mutex *mutex, int set)
{
	static int	dead;
	int			ret;

	pthread_mutex_lock(&mutex->mutex);
	if (set)
		dead = 1;
	ret = dead;
	pthread_mutex_unlock(&mutex->mutex);
	return (ret);
}

void	*check_death(void *data)
{
	t_philo	*phi;

	phi = (t_philo *)data;
	while (1)
	{
		if (get_value(phi->flag) == EXIT)
			return (NULL);
		if (if_death(phi, phi->info))
		{
			print_log(DEATH, phi);
			death(phi->print, 1);
		}
		usleep(200);
	}
}

void	monitor(t_philo *phi, size_t size)
{
	size_t	i;
	size_t	count;

	count = size;
	while (count)
	{
		i = 0;
		while (i < size && count)
		{
			if (death(phi[i].print, 0))
			{
				stop_philo(phi, size);
				return ;
			}
			if (get_value(phi[i].flag) == END)
			{
				count--;
				set_value(phi[i].flag, STOP);
				pthread_join(phi[i].thread, NULL);
			}
			i++;
		}
	}
}
