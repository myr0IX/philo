/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:56 by macassag          #+#    #+#             */
/*   Updated: 2024/03/15 16:45:54 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_death(t_philo **data)
{
	t_philo	*philo;
	int		death;

	philo = *data;
	if (philo->data->death)
		return ;
	printf(DEATH, philo->time, philo->index);
	death = 1;
	philo->data->death = &death;
	usleep(2000000);
}

int	print_log(char *msg, t_philo **data)
{
	size_t			life_time;
	t_philo 		*philo;
	int				r;

	philo = *data;
	philo->print = 1;
	pthread_mutex_lock(philo->data->lock_print);
	life_time = (philo->time - philo->last_eat);
	r = 0;
	if (philo->data->death || philo->data->error)
		r = -1;
	else if (life_time > philo->info.time_die)
	{
		ft_death(data);
		r = -1;
	}
	else
		printf(msg, philo->time, philo->index);
	pthread_mutex_unlock(philo->data->lock_print);
	philo->print = 0;
	return (r);
}
