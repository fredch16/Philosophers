/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innitmate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:21:12 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/17 17:51:48 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	mallocation_station(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->num_phils);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_phils);
	data->write = malloc(sizeof(pthread_mutex_t) * 1);
	data->lock = malloc(sizeof(pthread_mutex_t) * 1);
	data->philes = malloc(sizeof(t_socrates) * data->num_phils);
	return (0);
}

int	init_forks(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->num_phils)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = 0;
	data->philes[0].l_fork = &data->forks[0];
	data->philes[0].r_fork = &data->forks[data->num_phils - 1];
	i = 1;
	while (i < data->num_phils)
	{
		data->philes[i].l_fork = &data->forks[i];
		data->philes[i].r_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

int	enable_thinking(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_phils)
	{
		data->philes[i].data = data;
		data->philes[i].id = i + 1;
		data->philes[i].eating = 0;
		data->philes[i].status = 0;
		data->complete = 0;
		data->death_occured = 0;
		data->philes[i].fatty_factor = 0;
		data->time_of_start = 0;
		data->time_of_start = get_time(data);
		data->philes[i].meal_start = 0;
		i++;
	}
	pthread_mutex_init(data->write, NULL);
	pthread_mutex_init(data->lock, NULL);
	return (0);
}
