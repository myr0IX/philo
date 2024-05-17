/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:49 by macassag          #+#    #+#             */
/*   Updated: 2024/05/17 11:44:21 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_n_sleep(t_philo *phi)
{
	ft_usleep(phi->info.time_eat, phi);
	phi->eat++;
	if (get_time(phi) == SYS_ERR)
		return ;
	unset_value(phi->fork);
	unset_value(phi->next_fork);
	ft_usleep(phi->info.time_sleep, phi);
}

void	take_fork(t_philo *phi)
{
	int	count;

	count = 2;
	while (count)
	{
		if (check_value(phi->fork) == UNUSED
			|| check_value(phi->next_fork) == UNUSED)
		{
			print_log(FORK, phi);
			count--;
		}
	}
	if (!get_value(&phi->mutex, phi->flag) >= STOP)
		eat_n_sleep(phi);
}

void	*routine(void *data)
{
	t_philo	*phi;
	
	phi = (t_philo *) data;
	while (1)
	{
		if (get_value(&phi->mutex, phi->flag) == RUN)
			break ;
	}
	while (1)
	{
		print_log(THINKING, phi);
		take_fork(phi);
		if (get_value(&phi->mutex, phi->flag) >= STOP)
			break ;
		if (phi->info.max_eat && phi->eat == phi->info.max_eat)
			break ;
	}
	while (1)
		if (get_value(&phi->mutex, phi->flag) == EXIT)
			return ;
}

void	give_time(t_philo *phi, size_t size, t_time time)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		phi[i].start_time = time;
		set_value(&phi[i].mutex, &phi[i].flag, RUN);
		i++;
	}
}

void	stop_philo(t_philo *phi, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		set_value(&phi[i].mutex, phi[i].flag, EXIT);
		pthread_join(phi[i++].thread, NULL);
	}
}

void	ft_philo(t_philo *phi, size_t size)
{
	size_t	i;
	t_time	time;

	i = 0;
	while (i < size)
	{
		pthread_create(phi[i].thread, NULL, routine, &phi[i]);
		i++;
	}
	time = get_current_time(MILLI);
	give_time(phi, size, time);
}
