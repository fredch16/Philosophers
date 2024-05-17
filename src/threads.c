/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:32:05 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/17 16:30:04 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *fakephilo)
{
	t_socrates	*philo;

	philo = (t_socrates*)fakephilo;
	pthread_mutex_lock(philo->data->lock);
	while (!philo->data->complete && !philo->data->deathOccured)
	{
		pthread_mutex_unlock(philo->data->lock);
		get_forks(philo);
		eat(philo);
		go_sleep(philo);
		pthread_mutex_lock(philo->data->lock);
	}
	pthread_mutex_unlock(philo->data->lock);
	return (NULL);
}

void	*supervisor(void *fake)
{
	t_socrates *numba1;
	int	i;

	i = 0;
	numba1 = (t_socrates*)fake;
	pthread_mutex_lock(numba1->data->lock);
	while (!numba1->data->complete && !numba1->data->deathOccured)
	{
		pthread_mutex_unlock(numba1->data->lock);
		i = 0;
		while (!numba1->data->deathOccured && i < numba1->data->numPhils)
		{
			pthread_mutex_lock(numba1->data->lock);
			if (get_time(numba1->data) - numba1->data->philes[i].mealStart > numba1->data->timeToDie)
			{
				announce_death(numba1, i + 1);
				pthread_mutex_unlock(numba1->data->lock);
				return (NULL);
			}
			else if (numba1->data->fattyCount == numba1->data->numPhils)
			{
				numba1->data->complete = 1;
				pthread_mutex_unlock(numba1->data->lock);
				return (NULL);
			}
			pthread_mutex_unlock(numba1->data->lock);
			i++;
		}
		pthread_mutex_lock(numba1->data->lock);
	}
	pthread_mutex_unlock(numba1->data->lock);
	return (NULL);
}

int	thread_init(t_data *data)
{
	int				i;
	pthread_t		t0;

	i = 0;
	if (data->numTimesPhilMustEat > 0)
	{
		if (pthread_create(&t0, NULL, &supervisor, &data->philes[0]))
			return (error("TH_ERR", data));
	}
	while (i < data->numPhils)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philes[i]))
			return (error(TH_ERR, data));
		i++;
	}
	i = 0;
	if (pthread_join(t0, NULL))
	{
		return (error(JOIN_ERR, data));
	}
	while (i < data->numPhils)
	{
		if (pthread_join(data->tid[i], NULL))
			return (error(JOIN_ERR, data));
		i++;
	}
	ft_exit(data);
	return (0);
}
