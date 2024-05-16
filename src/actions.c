/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:40:37 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/16 22:30:21 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <pthread.h>

void	eat(t_socrates *philo)
{
	if (!philo->data->complete && !philo->data->deathOccured)
	{
	philo->mealStart = get_time(philo->data);
	philo->fattyFactor++;
	printf("%lu %d %s\n", get_time(philo->data), philo->id, EATING);
	if (philo->fattyFactor == philo->data->numTimesPhilMustEat)
	{
		philo->data->fattyCount++;
	}
	ft_usleep(philo->data->timeOfEat, philo->data);
	pthread_mutex_unlock(philo->lFork);
	// write_request(philo, DROPHALF);
	pthread_mutex_unlock(philo->rFork);
	// write_request(philo, );
	}
}

void	get_forks(t_socrates *philo)
{
	if (!philo->data->complete && !philo->data->deathOccured)
	{
		if ((philo->id % 2) == 0)
		{
			pthread_mutex_lock(philo->lFork);
			write_request(philo, TAKE_FORKS);
			if (!philo->data->complete && !philo->data->deathOccured)
			{
				pthread_mutex_lock(philo->rFork);
				write_request(philo, TAKE_FORKS);
			}
			else
			{
				pthread_mutex_unlock(philo->lFork);
				printf("dr111opo\n");
			}
		}
		else
		{
			pthread_mutex_lock(philo->rFork);
			write_request(philo, TAKE_FORKS);
			if (!philo->data->complete && !philo->data->deathOccured)
			{
				pthread_mutex_lock(philo->lFork);
				write_request(philo, TAKE_FORKS);
			}
			else
			{
				pthread_mutex_lock(philo->rFork);
				printf("dropo\n");
			}
		
		}
	}
}

void	go_sleep(t_socrates *philo)
{
	if (!philo->data->complete && !philo->data->deathOccured)
	{
	write_request(philo, SLEEPING);
	ft_usleep(philo->data->timeOfSleep, philo->data);
	write_request(philo, THINKING);
	}
}
