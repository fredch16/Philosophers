/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:40:37 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/14 15:09:06 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <pthread.h>

void	eat(t_socrates *philo)
{
	philo->mealStart = get_time(philo->data);
	printf("%lu - Fatty %d %s%d\n", get_time(philo->data), philo->id, EATBURGER, philo->fattyFactor);
	philo->fattyFactor++;
	if (philo->fattyFactor == philo->data->numTimesPhilMustEat)
	{
		philo->data->fattyCount++;
	}
	ft_usleep(philo->data->timeOfEat, philo->data);
	pthread_mutex_unlock(philo->lFork);
	printf("%lu - Fatty %d %s\n", get_time(philo->data), philo->id, DROPHALF);
	pthread_mutex_unlock(philo->rFork);
	printf("%lu - Fatty %d %s\n", get_time(philo->data), philo->id, DROPOHALF);
}

void	get_forks(t_socrates *philo)
{
	//fix odd and even phils
	pthread_mutex_lock(philo->lFork);
	printf("%lu - Fatty %d %s\n", get_time(philo->data), philo->id, HALFBURGER);
	pthread_mutex_lock(philo->rFork);
	printf("%lu - Fatty %d %s\n", get_time(philo->data), philo->id, OHALFBURGER);
}

void	go_sleep(t_socrates *philo)
{
	printf("%lu - Fatty %d %s\n", get_time(philo->data), philo->id, NAP);
	ft_usleep(philo->data->timeOfSleep, philo->data);
	printf("%lu - Fatty %d %s\n", get_time(philo->data), philo->id, WOKE);
}
