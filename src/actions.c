/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:40:37 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/17 16:33:24 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <pthread.h>

void	eat(t_socrates *philo)
{
	// pthread_mutex_lock(philo->data->lock);
	if (!philo->data->complete && !philo->data->deathOccured)
	{
	pthread_mutex_lock(philo->data->lock);
	philo->mealStart = get_time(philo->data);
	philo->fattyFactor++;
	printf("%lu %d %s\n", get_time(philo->data), philo->id, EATING);
	if (philo->fattyFactor == philo->data->numTimesPhilMustEat)
	{
		philo->data->fattyCount++;
	}
	pthread_mutex_unlock(philo->data->lock);
	ft_usleep(philo->data->timeOfEat, philo->data);
	pthread_mutex_unlock(philo->lFork);
	pthread_mutex_unlock(philo->rFork);
	// pthread_mutex_unlock(philo->data->lock);
	}
}

void	get_forks(t_socrates *philo)
{
	if (!philo->data->complete && !philo->data->deathOccured)
	{
		if (philo->data->numPhils == 1)
		{
			pthread_mutex_lock(philo->rFork);
			write_request(philo, TAKE_FORKS);
			ft_usleep(philo->data->timeToDie - get_time(philo->data) + 5, philo->data);
			pthread_mutex_unlock(philo->rFork);
		}
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
			}
		}
		else if ((philo->id % 2) != 0)	
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
				pthread_mutex_unlock(philo->rFork);
			}
		
		}
	}
}

void	go_sleep(t_socrates *philo)
{
	// pthread_mutex_lock(philo->data->lock);
	if (!philo->data->complete && !philo->data->deathOccured)
	{
		// pthread_mutex_unlock(philo->data->lock);
		write_request(philo, SLEEPING);
		ft_usleep(philo->data->timeOfSleep, philo->data);
		write_request(philo, THINKING);
	}
}
