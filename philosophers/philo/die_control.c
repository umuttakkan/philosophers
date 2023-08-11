/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:45:05 by uakkan            #+#    #+#             */
/*   Updated: 2023/08/10 23:29:06 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdio.h"
#include "unistd.h"

void	one_philo_die(t_table *data)
{
	pthread_mutex_lock(&data->write);
	printf("%llu %d died\n", ms() - data->start, data->philo->philo_id + 1);
	pthread_mutex_unlock(&data->write);
}

int	philo_die(t_table *data, int i)
{
	pthread_mutex_lock(&data->_last_eat);
	if ((ms() - data->philo[i].last_eat) >= (uint64_t)data->time_to_die)
	{
		pthread_mutex_unlock(&data->_last_eat);
		pthread_mutex_lock(&data->write);
		printf("%llu %d died\n", ms() - data->start,
			data->philo[i].philo_id + 1);
		pthread_mutex_unlock(&data->write);
		pthread_mutex_lock(&data->data);
		data->philo_dead = 0;
		pthread_mutex_unlock(&data->data);
		return (1);
	}
	return (0);
}

void	*die_control(void *args)
{
	t_table	*data;
	int		i;
	int		j;

	data = (t_table *)args;
	i = 0;
	j = 1;
	if (data->number_of_philo == 1)
		one_philo_die(data);
	pthread_mutex_lock(&data->_eat_control);
	while (data->number_of_philo > 1
		&& data->number_of_philo != data->eat_control)
	{
		pthread_mutex_unlock(&data->_eat_control);
		if (philo_die(data, i))
			break ;
		pthread_mutex_unlock(&data->_last_eat);
		i++;
		if (++j > data->number_of_philo)
			i = 0;
		usleep(100);
		pthread_mutex_lock(&data->_eat_control);
	}
	pthread_mutex_unlock(&data->_eat_control);
	return (NULL);
}
