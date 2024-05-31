/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznty <hznty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:05:16 by macassag          #+#    #+#             */
/*   Updated: 2024/05/31 10:43:10 by hznty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	get_current_time(int flag)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == SYS_ERR)
	{
		write(2, "gettimeofday() error\n", 22);
		return (SYS_ERR);
	}
	if (flag == MILLI)
		return (time.tv_sec * 1000 + time.tv_usec / 1000);
	if (flag == MICRO)
		return (time.tv_sec * 1e6 + time.tv_usec);
	return (0);
}

t_time	get_time(t_philo *philo, t_time given_time)
{
	t_time			time;
	static t_time	start_time;

	time = get_current_time(MILLI);
	if (time < 0)
	{
		set_value(philo->flag, ERROR);
		return (SYS_ERR);
	}
	if (given_time != 0)
		start_time = given_time;
	return (time - start_time);
}

void	ft_usleep(size_t time, t_philo *philo)
{
	t_time	start;

	start = get_current_time(MILLI);
	if (start < 0)
	{
		set_value(philo->flag, ERROR);
		return ;
	}
	while (get_current_time(MILLI) - start < (t_time) time)
	{
		if (get_value(philo->flag) >= STOP)
			break ;
		usleep(500);
	}
}
