/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:58:00 by macassag          #+#    #+#             */
/*   Updated: 2024/06/05 13:47:09 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	skip_white_space(const char *nptr)
{
	size_t	i;

	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	return (i);
}

long	ft_atoll(const char *nptr)
{
	long	result;
	size_t	i;
	int		neg;

	result = 0;
	neg = 1;
	i = skip_white_space(nptr);
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i++] == '-')
			neg = -1;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (((result * 10) + (nptr[i] - '0')) / 10 != result)
		{
			if (neg == 1)
				return (-1);
			if (neg == -1)
				return (0);
		}
		result = (result * 10) + (nptr[i++] - '0');
	}
	return (result * neg);
}
