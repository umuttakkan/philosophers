/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:10:33 by uakkan            #+#    #+#             */
/*   Updated: 2023/08/10 22:41:56 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdio.h"
#include "stdlib.h"

pthread_mutex_t	*mutex_init(t_table *data)
{
	int				i;
	pthread_mutex_t	*tmp;

	i = 0;
	tmp = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (!tmp)
	{
		free(data);
		return (NULL);
	}
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&tmp[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->data, NULL);
	pthread_mutex_init(&data->_last_eat, NULL);
	pthread_mutex_init(&data->_eat_control, NULL);
	return (tmp);
}

t_table	*table_init(int argc, char **argv)
{
	t_table	*data;

	if (check_only_number(argc, argv))
	{
		printf("Error! Only Number!");
		return (NULL);
	}
	data = malloc(sizeof(t_table));
	if (!data)
		return (NULL);
	data->number_of_philo = no_negative_atoi(argv[1]);
	data->time_to_die = no_negative_atoi(argv[2]);
	data->time_to_eat = no_negative_atoi(argv[3]);
	data->time_to_sleep = no_negative_atoi(argv[4]);
	if (argv[5])
		data->must_eat = no_negative_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->fork = mutex_init(data);
	data->philo_dead = 1;
	data->start = ms();
	data->eat_control = 0;
	return (data);
}

void	philo_init(t_table *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philo)
	{
		free(data->fork);
		free(data);
		return ;
	}
	while (i < data->number_of_philo)
	{
		data->philo[i].philo_id = i;
		data->philo[i].r_fork = i;
		data->philo[i].l_fork = (i + 1) % data->number_of_philo;
		data->philo[i].last_eat = 0;
		data->philo[i].table = data;
		data->philo[i]._must_eat = 0;
		data->philo[i].last_eat = ms();
		i++;
	}
}
