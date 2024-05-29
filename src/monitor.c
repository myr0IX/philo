/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 08:35:54 by macassag          #+#    #+#             */
/*   Updated: 2024/05/29 15:37:21 by macassag         ###   ########.fr       */
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
	// printf("reslut %ld\n", result);
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
		if (get_value(phi->flag) == STOP)
			return (NULL);
		if (if_death(phi, phi->info))
		{
			print_log(DEATH, phi);
			set_value(phi->flag, DEAD);
			death(phi->print, 1);
			return (NULL);
		}
	}
}

void	monitor(t_philo *phi, size_t size)
{
	size_t	i;
	t_time	flag;
	size_t	count;

	flag = 0;
	count = size;
	while (1)
	{
		i = 0;
		while (count)
		{
			if (get_value(phi[i].flag) == STOP)
			{
				count--;
				set_value(phi[i].flag, EXIT);
				pthread_join(phi[i].thread, NULL);
			}
			if (death(phi[i].print, 0))
			{
				stop_philo(phi, size);	
				exit_child(phi, size);
				return ;
			}
			i++;
		}
	}
	stop_philo(phi, size);
}
