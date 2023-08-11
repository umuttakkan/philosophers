/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 00:15:11 by uakkan            #+#    #+#             */
/*   Updated: 2023/08/10 23:28:30 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	*start_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if ((philo->philo_id + 1) % 2 == 0)
		ft_sleep(50);
	pthread_mutex_lock(&philo->table->data);
	while (philo->table->philo_dead)
	{
		pthread_mutex_unlock(&philo->table->data);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
		pthread_mutex_lock(&philo->table->data);
	}
	pthread_mutex_unlock(&philo->table->data);
	return (NULL);
}

void	*eat_control(void *args)
{
	t_table	*data;

	data = (t_table *)args;
	while (data->must_eat != -1)
	{
		pthread_mutex_lock(&data->_eat_control);
		if (data->number_of_philo == data->eat_control)
		{
			pthread_mutex_lock(&data->data);
			data->philo_dead = 0;
			pthread_mutex_unlock(&data->data);
			pthread_mutex_unlock(&data->_eat_control);
			break ;
		}
		pthread_mutex_unlock(&data->_eat_control);
	}
	return (NULL);
}

void	start_threads(t_table *data)
{
	int			i;
	pthread_t	x;
	pthread_t	y;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_create(&data->philo[i].thread, NULL,
			start_philo, (void *)&data->philo[i]);
		i++;
	}
	pthread_create(&x, NULL, &die_control, data);
	pthread_create(&y, NULL, &eat_control, data);
	i = 0;
	while (i < data->number_of_philo)
	{
		if (data->number_of_philo == 1)
			pthread_detach(data->philo[i].thread);
		else
			pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(x, NULL);
	pthread_join(y, NULL);
}

void	the_end(t_table *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->_last_eat);
	pthread_mutex_destroy(&data->data);
	pthread_mutex_destroy(&data->_eat_control);
	while (++i < data->number_of_philo)
		pthread_mutex_destroy(&data->fork[i]);
	free(data->fork);
	free(data->philo);
	free(data);
}
