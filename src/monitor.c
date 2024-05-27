/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 08:35:54 by macassag          #+#    #+#             */
/*   Updated: 2024/05/19 16:33:07 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop_philo(t_philo *phi, size_t size)
{
	size_t	i;
	int		flag;

	i = 0;
	// *flag = 0;
	// printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	while (i < size)
	{
		flag = get_int(&phi[i].mutex, &phi[i].flag);
		// printf("philo %zu : flag = %i\n", i + 1 ,  flag);
		if (flag != EXIT)
		{
			set_value(&phi[i].mutex, &phi[i].flag, EXIT);
			pthread_join(phi[i].thread, NULL);
		}
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
	result = get_time_value(&phi->mutex, &phi->last_eat) + \
		(t_time) info.life_time;
	if (result < time)
		return (1);
	return (0);
}

void	monitor(t_philo *phi, size_t size)
{
	size_t	i;
	int		flag;
	size_t	count;

	flag = 0;
	count = size;
	while (count)
	{
		i = 0;
		while (i < size)
		{
			if (check_death(&phi[i], phi->info) == 1)
			{
				stop_philo(phi, size);	
				print_log(DEATH, phi);
				return ;
			}
			flag = get_int(&phi[i].mutex, &phi[i].flag);
			if (flag >= STOP)
			{
				set_value(&phi[i].mutex, &phi[i].flag, EXIT);
				pthread_join(phi[i].thread, NULL);
				count--;
			}
			i++;
		}
	}
	stop_philo(phi, size);
}
