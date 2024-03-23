/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:02:59 by macassag          #+#    #+#             */
/*   Updated: 2024/03/23 14:03:22 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (-1);
	return (1);
}

static int	parsing(char **argv)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (argv[++j])
	{
		i = 0;
		while (argv[j][i])
			if (ft_isdigit(argv[j][i++]) == -1)
				return (printf(ARG_ERROR), -1);
		if (ft_atoi(argv[j]) > INT_MAX || ft_atoi(argv[j]) < INT_MIN)
			return (printf(ARG_ERROR), -1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	if (parsing(argv) == -1)
		return (0);
	if (argc == 5)
	{
		info.phi_nbr = ft_atoi(argv[1]);
		info.time_die = ft_atoi(argv[2]);
		info.time_eat = ft_atoi(argv[3]);
		info.time_sleep = ft_atoi(argv[4]);
		init_philo(info);
	}
	else if (argc == 6)
	{
		info.phi_nbr = ft_atoi(argv[1]);
		info.time_die = ft_atoi(argv[2]);
		info.time_eat = ft_atoi(argv[3]);
		info.time_sleep = ft_atoi(argv[4]);
		info.max_eat = ft_atoi(argv[5]);
		init_philo(info);
	}
	else
		printf("%s%s%s%s", ARG_ERROR, ARG_ERROR2, ARG_ERROR3, ARG_ERROR4);
	return (0);
}
