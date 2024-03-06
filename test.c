/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:01:38 by macassag          #+#    #+#             */
/*   Updated: 2024/03/05 10:54:49 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_msg(int flag, char *msg)
{
	printf("%s\n", msg);
	if (flag == -1)
		exit(EXIT_SUCCESS);
}

void	*ft_test(void *data)
{
	t_test	*test;
	int		i;

	i = 0;
	test = (t_test *)data;
	while (i < 50)
	{
		pthread_mutex_lock(&test->ft_print.mutex);
		printf("%i\n", test->ft_print.count);
		if (test->ft_print.count % 2 == 0)
			printf("aaaaaaaaaaaaaa\n\n");
		else
			printf("bbbbbbbbbbbbbbbb\n\n");
		pthread_mutex_unlock(&test->ft_print.mutex);
		usleep(500);
		pthread_mutex_lock(&test->ft_print.mutex);
		test->ft_print.count++;
		pthread_mutex_unlock(&test->ft_print.mutex);
		i++;
	}
	test->ft_print.ft_print(4, 1);
	return (NULL);
}

int	main(void)
{
	struct timeval	start;
	struct timeval	end;
	pthread_t		td1;
	pthread_t		td2;
	t_test			test;
	t_philo			*philo;

	gettimeofday(&start, NULL);
	memset(&test, 0, sizeof(t_test));
	pthread_mutex_init(&test.ft_print.mutex, NULL);
	test.ft_print.ft_print = &write_msg;
	pthread_create(&td1, NULL, ft_test, &test);
	pthread_create(&td2, NULL, ft_test, &test);
	pthread_join(td1, NULL);
	pthread_join(td2, NULL);


	test_phi = malloc(sizeof(t_data));
	memset(test_phi, 0, sizeof(t_data));
	philo = *test_phi->philos;
	int i = 1;
	while (philo->index == 0)
	{
		philo->index = i++;
		philo = philo->next;
	}
	gettimeofday(&end, NULL);
	printf("\ntime : [%ld]\n\n", end.tv_sec - start.tv_sec);
	return (0);
}
