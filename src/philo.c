/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:49 by macassag          #+#    #+#             */
/*   Updated: 2024/05/28 10:08:33 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_n_sleep(t_philo *phi)
{
	t_time	time;
	int		ret;
	
	print_log(EATING, phi);
	ft_usleep(phi->info.time_eat, phi);
	phi->eat++;
	time = get_time(phi);
	if (time == SYS_ERR)
	{
		set_value(&phi->mutex, &phi->flag, ERROR);
		return ;
	}
	set_time(&phi->fork->mutex, &phi->last_eat, time);
	ret = get_int(&phi->mutex, &phi->flag);
	if (ret < STOP)
		print_log(SLEEPING, phi);
	set_value(&phi->fork->mutex, &phi->fork->use, UNUSED);
	set_value(&phi->next_fork->mutex, &phi->next_fork->use, UNUSED);
	if (ret < STOP)
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
	ret = get_int(&phi->mutex, &phi->flag);
	if (ret < STOP)
		eat_n_sleep(phi);
	else
	{
		set_value(&phi->fork->mutex, &phi->fork->use, UNUSED);
		set_value(&phi->next_fork->mutex, &phi->next_fork->use, UNUSED);
	}
}

void	wait_start(t_philo *phi)
{
	int		ret;

	ret = 0;
	while (1)
	{
		ret = get_int(&phi->mutex, &phi->flag);
		if (ret == RUN)
			break ;
	}
}

void	*routine(void *data)
{
	t_philo	*phi;
	int		ret;
	
	phi = (t_philo *) data;
	ret = 0;
	wait_start(phi);
	print_log(THINKING, phi);
	if (phi->index % 2 == 0)
		usleep(phi->info.time_eat / 2);
	while (1)
	{
		if (phi->eat)
			print_log(THINKING, phi);
		take_fork(phi);
		ret = get_int(&phi->mutex, &phi->flag);
		if (ret >= STOP)
			break ;
		if (phi->info.max_eat && phi->eat == phi->info.max_eat)
			break ;
	}
	// printf("exit\n");
	set_value(&phi->fork->mutex, &phi->flag, STOP);
	while (1)
	{
		ret = get_int(&phi->mutex, &phi->flag);
		if (ret == EXIT)
			return (NULL);
	}
}


void	ft_philo(t_philo *phi, size_t size)
{
	size_t	i;
	t_time	time;

	i = 0;
	while (i < size)
	{
		pthread_create(&phi[i].thread, NULL, routine, &phi[i]);
		i++;
	}
	time = get_current_time(MILLI);
	give_time(phi, size, time);
	monitor(phi, size);
	free_struct(phi, phi->info.phi_nbr);
}
