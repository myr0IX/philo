/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:48:20 by macassag          #+#    #+#             */
/*   Updated: 2024/03/21 16:08:11 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(void *data)
{
	if (data)
		free(data);
}

t_data	*del_mutex(t_data *data)
{
	
	mutex_destroy(&data->lock_print);
	mutex_destroy(&data->lock_start);
	mutex_destroy(&data->lock_eat);
	mutex_destroy(&data->lock_data);
	ft_free(data);
	return (NULL);
}

void	free_lst(t_philo **data)
{
	t_philo	*tmp;
	t_philo *philo;

	philo = *data;
	philo->prev->next = NULL;
	while (philo->next != NULL)
	{
		tmp = philo;
		philo = philo->next;
		mutex_destroy(&tmp->r_fork->lock_fork);
		ft_free(tmp->r_fork);
		ft_free(tmp);
	}
	ft_free(philo->r_fork);
	ft_free(philo);
}

void	error_lst(t_philo **data, char *msg)
{
	t_philo	*philo;

	philo = *data;
	(void)msg;
	del_mutex(philo->data);
	free_lst(data);
	exit(EXIT_FAILURE);
}
