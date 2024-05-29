/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:49 by macassag          #+#    #+#             */
/*   Updated: 2024/05/29 15:35:47 by macassag         ###   ########.fr       */
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
	{
		set_value(phi->flag, ERROR);
		return ;
	}
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
		usleep(100);
	}
	eat_n_sleep(phi);
}

void	wait_start(t_philo *phi)
{
	int		ret;

	(void)phi;
	ret = 0;
	pthread_create(&phi->check_death, NULL, check_death, phi);
	pthread_detach(phi->check_death);
	while (1)
	{
		ret = get_value(phi->flag);
		if (ret >= STOP)
			break ;
	}
}

void	*routine(void *data)
{
	t_philo	*phi;
	t_time		ret;
	
	phi = (t_philo *) data;
	wait_start(phi);
	return (NULL);
	if (phi->index % 2 == 0)
		usleep(phi->info.time_eat / 2);
	while (1)
	{
		if (phi->eat)
			print_log(THINKING, phi);
		take_fork(phi);
		ret = get_value(phi->flag);
		if (ret >= STOP)
			break ;
		if (phi->info.max_eat && phi->eat == phi->info.max_eat)
			break ;
	}
	set_value(phi->flag, STOP);
	while (1)
	{
		ret = get_value(phi->flag);
		if (ret == EXIT)
			return (NULL);
		usleep(50);
	}
}

void	ft_philo(t_philo *phi, size_t size)
{
	size_t	i;
	t_time	time;

	i = 0;
	time = get_current_time(MILLI);
	if (time < 0)
		return ;
	get_time(phi, time);
	// printf("time to time = %zu\n", time);
	while (i < size)
	{
		// phi[i].last_eat->value = time;
		pthread_create(&phi[i].thread, NULL, routine, &phi[i]);
		i++;
	}
	printf("time to threading philo = %zu\n", get_time(phi, 0));
	// stop_philo(phi, size);
	while (1)
		;
	exit_child(phi, size);
	return ;
	run_philo(phi->print, time);
	monitor(phi, size);
	free_struct(phi, phi->info.phi_nbr);
}
