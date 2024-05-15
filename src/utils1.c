/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:10:16 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/15 23:57:49 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <stdlib.h>

void	clearData(t_data *data)
{
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philes)
		free(data->philes);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numPhils)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	clearData(data);
}

int	error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}

u_int64_t	get_time(t_data *data)
{
	//calculates the current time in ms and returns it as a uint64
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000) - data->timeOfStart);
}

int	ft_usleep(useconds_t time, t_data *data)
{
	uint64_t	start;
	uint64_t	elapsed;

	start = get_time(data);
	elapsed = get_time(data);
	while (elapsed - start < time)
	{
		usleep(250);
		elapsed = get_time(data);
	}
	return (0);
}

void	announce_death(t_socrates *phil, int id)
{
	printf("%lu - Fatty %d could not munch fast enough\n\n", get_time(phil->data), id);
	phil->data->deathOccured = 1;
	ft_exit(phil->data);
	exit(EXIT_SUCCESS);
	
}
