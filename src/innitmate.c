/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innitmate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:21:12 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/14 19:12:20 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	mallocationStation(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->numPhils);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->numPhils);
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
		data->philes[i].fattyFactor = 1;
		data->timeOfStart = 0;
		// pthread_mutex_init(&data->philes[i].lock, NULL);
		i++;
	}
	return (0);
}
