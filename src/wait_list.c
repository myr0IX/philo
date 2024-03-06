/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:55:42 by macassag          #+#    #+#             */
/*   Updated: 2024/03/06 15:06:14 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_list(t_philo **data)
{
	t_philo			*philo;
	static size_t	wait_list;
	size_t			tmp;

	philo = *data;
	philo->wait_list = ++wait_list;
	tmp = wait_list;
	
	while ()
	{
		if (philo->wait_list < tmp)
			tmp = philo->wait_list;
	}
}
