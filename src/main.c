/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:02:59 by macassag          #+#    #+#             */
/*   Updated: 2024/05/29 13:00:45 by macassag         ###   ########.fr       */
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

t_mutex	*create_mutex(void)
{
	t_mutex	*mutex;

	mutex = (t_mutex *) malloc(sizeof(t_mutex));
	if (!mutex)
		return (NULL);
	memset(mutex, 0, sizeof(t_mutex));
	if (mutex_init(mutex->mutex) == -1)
		return (NULL);
	return (mutex);
}

int	init_mutex(t_philo *philo, t_mutex *print, t_info info)
{
	philo->print = print;
	philo->info = info;
	philo->fork = create_mutex();
	philo->mutex = create_mutex();
	philo->flag = create_mutex();
	// philo->start_time = create_mutex();
	philo->last_eat = create_mutex();
	// if (!philo->mutex || !philo->fork || !philo->flag
	// 	|| !philo->start_time || !philo->last_eat)
	// 	return (1);
	return (0);
}

static void	init_philo(t_info info)
{
	t_philo	*philo;
	size_t	i;
	t_mutex	*print;

	philo = NULL;
	philo = (t_philo*) malloc(info.phi_nbr * sizeof(t_philo));
	print = create_mutex();
	if (!philo || !print)
		return ;
	memset(philo, 0, sizeof(t_philo));
	i = 0;
	while (i < info.phi_nbr)
	{
		if (init_mutex(&philo[i], print, info))
		{
			free_struct(philo, i + 1);
			return ;
		}
		if (i + 1 == info.phi_nbr)
			philo[i].next_fork = philo[0].fork;
		if (i != 0)
			philo[i - 1].next_fork = philo[i].fork;
		philo[i].index = i + 1;
		i++;
	}
	// printf_mutex(philo, info.phi_nbr);
	// free_struct(philo, info.phi_nbr);
	ft_philo(philo, info.phi_nbr);
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
		info.life_time = ft_atoi(argv[2]);
		info.time_eat = ft_atoi(argv[3]);
		info.time_sleep = ft_atoi(argv[4]);
		init_philo(info);
	}
	else if (argc == 6)
	{
		info.phi_nbr = ft_atoi(argv[1]);
		info.life_time = ft_atoi(argv[2]);
		info.time_eat = ft_atoi(argv[3]);
		info.time_sleep = ft_atoi(argv[4]);
		info.max_eat = ft_atoi(argv[5]);
		init_philo(info);
	}
	else
		printf("%s", ARG_ERROR);
	return (0);
}
