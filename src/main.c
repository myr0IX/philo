/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:02:59 by macassag          #+#    #+#             */
/*   Updated: 2024/03/06 11:15:13 by macassag         ###   ########.fr       */
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
	{
		printf("Bad arguments !\n");
		printf("./philo\tnumber_of_philosophers\t");
		printf("time_to_die time_to_eat\ttime_to_sleep\t");
		printf("[number_of_times_each_philosopher_must_eat]\n");
	}
	return (0);
}
