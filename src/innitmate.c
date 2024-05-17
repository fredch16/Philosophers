/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innitmate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:21:12 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/17 13:46:47 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	mallocationStation(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->numPhils);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->numPhils);
	data->write = malloc(sizeof(pthread_mutex_t) * 1);
	data->lock = malloc(sizeof(pthread_mutex_t) * 1);
	data->philes = malloc(sizeof(t_socrates) * data->numPhils);
	return (0);
}

int	initForks(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->numPhils)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = 0;
	data->philes[0].lFork = &data->forks[0];
	data->philes[0].rFork = &data->forks[data->numPhils - 1];
	i = 1;
	while (i < data->numPhils)
	{
		data->philes[i].lFork = &data->forks[i];
		data->philes[i].rFork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

int	enableThinking(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numPhils)
	{
		data->philes[i].data = data;
		data->philes[i].id = i + 1;
		// data->philes[i].timeToDie = data->timeOfDeath;
		data->philes[i].eating = 0;
		data->philes[i].status = 0;
		data->complete = 0;
		data->deathOccured = 0;
		data->philes[i].fattyFactor = 0;
		data->timeOfStart = 0;
		data->timeOfStart = get_time(data);
		data->philes[i].mealStart = 0;
		// data->philes[i].mealStart = get_time(data);
		// pthread_mutex_init(&data->philes[i].lock, NULL);
		i++;
	}
	pthread_mutex_init(data->write, NULL);
	pthread_mutex_init(data->lock, NULL);
	return (0);
}
