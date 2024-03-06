/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:02:59 by macassag          #+#    #+#             */
/*   Updated: 2024/03/06 14:16:54 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	infos;

	memset(&infos, 0, sizeof(t_info));
	if (argc == 5)
	{
		infos.phi_nbr = ft_atoi(argv[1]);
		infos.time_die = ft_atoi(argv[2]);
		infos.time_eat = ft_atoi(argv[3]);
		infos.time_sleep = ft_atoi(argv[4]);
		init_philo(infos);
	}
	else if (argc == 6)
	{
		infos.phi_nbr = ft_atoi(argv[1]);
		infos.time_die = ft_atoi(argv[2]);
		infos.time_eat = ft_atoi(argv[3]);
		infos.time_sleep = ft_atoi(argv[4]);
		infos.eat_nbr = ft_atoi(argv[5]);
		init_philo(infos);
	}
	else
		printf("%s%s%s%s", ARG_ERROR, ARG_ERROR2, ARG_ERROR3, ARG_ERROR4);
	return (0);
}
