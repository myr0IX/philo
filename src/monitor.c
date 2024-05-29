/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 08:35:54 by macassag          #+#    #+#             */
/*   Updated: 2024/05/28 14:03:57 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	give_time(t_philo *phi, size_t size, t_time time)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		set_value(phi[i].start_time, time);
		set_value(phi[i].last_eat, time);
		// set_value(phi[i].flag, RUN);
		usleep(200);
		i++;
	}
	i = 0;
	while (i < size)
	{
		set_value(phi[i].flag, RUN);
		i++;
	}
}

void	stop_philo(t_philo *phi, size_t size)
{
	size_t	i;
	// int		flag;

	i = 0;
	while (i < size)
	{
		set_value(phi[i].flag, STOP);
		usleep(200);
		i++;
	}
}

void	exit_child(t_philo *phi, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		set_value(phi[i].flag, EXIT);
		pthread_join(phi[i].thread, NULL);
		i++;
	}
}

static int	check_death(t_philo *phi, t_info info)
{
	t_time	time;
	t_time	result;

	time = 0;
	result = 0;
	time = get_time(phi);
	if (time == SYS_ERR)
		return (SYS_ERR);
	result = get_value(phi->last_eat) + (t_time) info.life_time;
	if (result < time)
		return (1);
	return (0);
}

void	monitor(t_philo *phi, size_t size)
{
	size_t	i;
	t_time	flag;
	size_t	count;

	flag = 0;
	count = size;
	while (count)
	{
		i = 0;
		while (i < size)
		{
			if (check_death(&phi[i], phi->info))
			{
				stop_philo(phi, size);	
				print_log(DEATH, &phi[i]);
				exit_child(phi, size);
				return ;
			}
			i++;
		}
	}
	stop_philo(phi, size);
}
