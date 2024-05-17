/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:34:20 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/17 18:43:12 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <stdlib.h>

void	announce_death(t_socrates *phil, int id)
{
	pthread_mutex_lock(phil->data->lock);
	phil->data->death_occured = 1;
	printf("%lu %d died\n", get_time(phil->data), id);
	pthread_mutex_unlock(phil->data->lock);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	set_em_up(argc, argv, &data);
	if (thread_init(&data))
		return (1);
	exit(EXIT_SUCCESS);
	return (0);
}
