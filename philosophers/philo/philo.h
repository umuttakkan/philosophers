/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:40:23 by uakkan            #+#    #+#             */
/*   Updated: 2023/08/10 23:30:34 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h>
# include <pthread.h>

typedef struct s_philo
{
	int				philo_id;
	int				l_fork;
	int				r_fork;
	int				_must_eat;
	uint64_t		last_eat;
	pthread_t		thread;
	struct s_table	*table;
}			t_philo;

typedef struct s_table
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				eat_control;
	int				philo_dead;
	uint64_t		start;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
	pthread_mutex_t	data;
	pthread_mutex_t	_last_eat;
	pthread_mutex_t	_eat_control;
	t_philo			*philo;
}			t_table;

t_table		*table_init(int argc, char **argv);
int			no_negative_atoi(char *str);
int			check_only_number(int argc, char **argv);
void		philo_init(t_table *data);
void		philo_eating(t_philo *philo);
void		philo_sleeping(t_philo *philo);
void		philo_thinking(t_philo *philo);
void		start_threads(t_table *data);
void		*die_control(void *args);
void		ft_sleep(uint64_t time_to_eat);
uint64_t	ms(void);
void		the_end(t_table *data);
void		*eat_control(void *args);
int			negative_control(t_table *data);

#endif