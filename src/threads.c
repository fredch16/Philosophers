/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:32:05 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/16 22:01:31 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *fakephilo)
{
	t_socrates	*philo;

	philo = (t_socrates*)fakephilo;
	while (!philo->data->complete && !philo->data->deathOccured)
	{
		get_forks(philo);
		eat(philo);
		go_sleep(philo);
	}
	return (NULL);
}

void	*supervisor(void *fake)
{
	t_socrates *numba1;
	int	i;

	i = 0;
	numba1 = (t_socrates*)fake;

	while (!numba1->data->complete && !numba1->data->deathOccured)
	{
		i = 0;
		while (!numba1->data->deathOccured && i < numba1->data->numPhils)
		{
			if (get_time(numba1->data) - numba1->data->philes[i].mealStart > numba1->data->timeToDie)
			{
				announce_death(numba1, i + 1);
				return (NULL);
			}
			else if (numba1->data->fattyCount == numba1->data->numPhils)
			{
				numba1->data->complete = 1;
				// printf("All fatties are fat\n");
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int	thread_init(t_data *data)
{
	int				i;
	pthread_t		t0;

	i = 0;
	// data->timeOfStart = get_time(data);
	printf("%lu - Simulation has begun\n", get_time(data));
	if (data->numTimesPhilMustEat > 0)
	{
		//create a single overwatching thread that ensures nobody dyin
		if (pthread_create(&t0, NULL, &supervisor, &data->philes[0]))
			return (error("TH_ERR", data));
	}
	while (i < data->numPhils)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philes[i]))
			return (error(TH_ERR, data));
		// ft_usleep(1, data);
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
