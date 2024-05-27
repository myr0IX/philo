/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:48:20 by macassag          #+#    #+#             */
/*   Updated: 2024/05/19 12:14:10 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(void *data)
{
	if (data)
		free(data);
}

void	free_struct(t_philo *phi, size_t size)
{
	size_t	i;

	i = 0;
	mutex_destroy(&phi->print->mutex);
	ft_free(phi->print);
	while (i < size)
	{
		mutex_destroy(&phi[i].fork->mutex);
		mutex_destroy(&phi[i].mutex);
		ft_free(phi[i].fork);
		i++;
	}
	ft_free(phi);
}