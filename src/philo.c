/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:49 by macassag          #+#    #+#             */
/*   Updated: 2024/05/28 14:19:43 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_n_sleep(t_philo *phi)
{
	t_time	time;
	
	print_log(EATING, phi);
	ft_usleep(phi->info.time_eat, phi);
	phi->eat++;
	time = get_time(phi);
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
	int	ret;

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
	}
	ret = get_value(phi->flag);
	if (ret < STOP)
		eat_n_sleep(phi);
	else
	{
		set_value(phi->fork, UNUSED);
		set_value(phi->next_fork, UNUSED);
	}
}


void	wait_start(t_philo *phi)
{
	int		ret;

	// printf("phi %i\n", phi->index);
	ret = 0;
	while (1)
	{
		ret = get_value(phi->flag);
		if (ret == RUN)
			break ;
	}
}

void	*routine(void *data)
{
	t_philo	*phi;
	t_time		ret;
	
	phi = (t_philo *) data;
	ret = 0;
	// wait_start(phi);
	// print_log(THINKING, phi);
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
	// printf("exit\n");
	if (get_value(phi->flag) >= DEAD)
		return (NULL);
	set_value(phi->flag, STOP);
	while (1)
	{
		ret = get_value(phi->flag);
		// printf("ret = %zu\n", ret);
		if (ret == EXIT)
			return (NULL);
		usleep(500);
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
	while (i < size)
	{
		phi[i].start_time->value = time;
		phi[i].last_eat->value = time;
		print_log(THINKING, &phi[i]);
		pthread_create(&phi[i].thread, NULL, routine, &phi[i]);
		i += 2;
	}
	i = 1;
	while (i < size)
	{
		phi[i].start_time->value = time;
		phi[i].last_eat->value = time;
		print_log(THINKING, &phi[i]);
		pthread_create(&phi[i].thread, NULL, routine, &phi[i]);
		i += 2;
	}
	// give_time(phi, size, time);
	monitor(phi, size);
	free_struct(phi, phi->info.phi_nbr);
}
