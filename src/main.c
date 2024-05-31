/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznty <hznty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:02:59 by macassag          #+#    #+#             */
/*   Updated: 2024/05/31 11:16:13 by hznty            ###   ########.fr       */
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
		if (ft_atoll(argv[j]) > INT_MAX || ft_atoll(argv[j]) < 0)
			return (printf(ARG_ERROR), 1);
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
	philo->last_eat = create_mutex();
	if (!philo->mutex || !philo->fork || !philo->flag
		|| !philo->last_eat)
		return (1);
	return (0);
}

static int	init_philo(t_info info)
{
	t_philo	*philo;
	long	i;
	t_mutex	*print;

	if (!info.life_time|| !info.time_eat || !info.time_sleep || !info.phi_nbr)
		return (printf(ARG_ERROR), 1);
	philo = (t_philo*) malloc(info.phi_nbr * sizeof(t_philo));
	print = create_mutex();
	if (!philo || !print)
		return (1);
	memset(philo, 0, sizeof(t_philo));
	i = -1;
	while (++i < (long) info.phi_nbr)
	{
		if (init_mutex(&philo[i], print, info))
			return (free_struct(philo, i + 1), 1);
		if (i + 1 == (long) info.phi_nbr)
			philo[i].next_fork = philo[0].fork;
		if (i != 0)
			philo[i - 1].next_fork = philo[i].fork;
		philo[i].index = i + 1;
	}
	return (ft_philo(philo, info.phi_nbr), 0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	if (parsing(argv))
		return (1);
	if (argc == 5)
	{
		info.phi_nbr = ft_atoll(argv[1]);
		info.life_time = ft_atoll(argv[2]);
		info.time_eat = ft_atoll(argv[3]);
		info.time_sleep = ft_atoll(argv[4]);
		init_philo(info);
	}
	else if (argc == 6)
	{
		info.phi_nbr = ft_atoll(argv[1]);
		info.life_time = ft_atoll(argv[2]);
		info.time_eat = ft_atoll(argv[3]);
		info.time_sleep = ft_atoll(argv[4]);
		info.max_eat = ft_atoll(argv[5]);
		init_philo(info);
	}
	else
		printf("%s", ARG_ERROR);
	return (0);
}
