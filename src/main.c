/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:02:59 by macassag          #+#    #+#             */
/*   Updated: 2024/03/15 10:31:16 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	info;

	memset(&info, 0, sizeof(t_info));
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
