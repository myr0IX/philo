/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:48:20 by macassag          #+#    #+#             */
/*   Updated: 2024/06/05 11:53:45 by macassag         ###   ########.fr       */
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
		mutex_destroy(&phi[i].last_eat->mutex);
		mutex_destroy(&phi[i].mutex->mutex);
		mutex_destroy(&phi[i].flag->mutex);
		mutex_destroy(&phi[i].fork->mutex);
		ft_free(phi[i].last_eat);
		ft_free(phi[i].mutex);
		ft_free(phi[i].flag);
		ft_free(phi[i].fork);
		i++;
	}
	ft_free(phi);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (!s1)
		return (-1);
	while (str1[i] && str2[i] && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (str1[i] != str2[i] && i < n)
		return (str1[i] - str2[i]);
	return (0);
}
