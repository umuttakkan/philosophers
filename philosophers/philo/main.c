/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:07:46 by uakkan            #+#    #+#             */
/*   Updated: 2023/08/10 23:26:10 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdio.h"

int	main(int argc, char **argv)
{
	t_table	*data;

	if ((argc < 5) || (argc > 6))
	{
		printf("Arguments Error!");
		return (0);
	}
	data = table_init(argc, argv);
	if (!data)
		return (0);
	philo_init(data);
	start_threads(data);
	the_end(data);
}
