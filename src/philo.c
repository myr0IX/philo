/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznty <hznty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:49 by macassag          #+#    #+#             */
/*   Updated: 2024/05/31 10:53:11 by hznty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_n_sleep(t_philo *phi)
{
	t_time	time;
	
	print_log(EATING, phi);
	ft_usleep(phi->info.time_eat, phi);
	phi->eat++;
	time = get_time(phi, 0);
	if (time == SYS_ERR)
		return ;
	set_value(phi->last_eat, time);
	print_log(SLEEPING, phi);
	set_value(phi->fork, UNUSED);
	set_value(phi->next_fork, UNUSED);
	ft_usleep(phi->info.time_sleep, phi);
}

void	take_fork(t_philo *phi)
{
	int	count;

	count = 2;
	while (count)
	{
		if (check_value(phi->fork) == 1)
		{
			print_log(FORK, phi);
			count--;
		}
		if (check_value(phi->next_fork) == 1)
		{
			print_log(FORK, phi);
			count--;
		}
		usleep(500);
	}
	eat_n_sleep(phi);
}

void	*routine(void *data)
{
	t_philo	*phi;

	phi = (t_philo *) data;
	pthread_create(&phi->check_death, NULL, check_death, phi);
	pthread_detach(phi->check_death);
	while (get_value(phi->flag) < STOP)
	{
		if (phi->eat)
			print_log(THINKING, phi);
		take_fork(phi);
		if (phi->info.max_eat && phi->eat == phi->info.max_eat)
			break ;
	}
	set_value(phi->flag, STOP);
	return (NULL);
}

void	run_thread(t_philo *phi, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		pthread_create(&phi[i].thread, NULL, routine, &phi[i]);
		i = i + 2;
	}
	usleep(phi->info.time_eat / 10);
	i = 1;
	while (i < size)
	{
		pthread_create(&phi[i].thread, NULL, routine, &phi[i]);
		i = i + 2;
	}
}

void	ft_philo(t_philo *phi, size_t size)
{
	t_time	time;

	time = get_current_time(MILLI);
	if (time < 0)
		return ;
	get_time(phi, time);
	run_thread(phi, size);
	monitor(phi, size);
	free_struct(phi, phi->info.phi_nbr);
}
