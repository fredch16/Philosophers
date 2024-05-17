/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:10:16 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/17 17:54:55 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <pthread.h>
#include <stdlib.h>

void	clear_data(t_data *data)
{
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philes)
		free(data->philes);
	if (data->write)
		free(data->write);
	if (data->lock)
		free(data->lock);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_phils)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(data->lock);
	pthread_mutex_destroy(data->write);
	clear_data(data);
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
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (uint64_t)1000)
		+ (tv.tv_usec / 1000) - data->time_of_start);
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
