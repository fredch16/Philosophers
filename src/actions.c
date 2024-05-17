/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:40:37 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/17 19:47:52 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <pthread.h>

void	eat(t_socrates *philo)
{
	pthread_mutex_lock(philo->data->lock);
	if (!philo->data->complete && !philo->data->death_occured)
	{
		pthread_mutex_unlock(philo->data->lock);
		philo->meal_start = get_time(philo->data);
		philo->fatty_factor++;
		printf("%lu %d %s\n", get_time(philo->data), philo->id, EATING);
		if (philo->fatty_factor == philo->data->eat_goal)
		{
			philo->data->fatty_count++;
		}
		ft_usleep(philo->data->time_of_eat, philo->data);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_lock(philo->data->lock);
	}
	pthread_mutex_unlock(philo->data->lock);
}

void	choose_fork(t_socrates *philo)
{
	if ((philo->id % 2) == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		write_request(philo, TAKE_FORKS);
		if (!philo->data->complete && !philo->data->death_occured)
		{
			pthread_mutex_lock(philo->r_fork);
			write_request(philo, TAKE_FORKS);
		}
		else
			pthread_mutex_unlock(philo->l_fork);
	}
	else if ((philo->id % 2) != 0)
	{
		pthread_mutex_lock(philo->r_fork);
		write_request(philo, TAKE_FORKS);
		if (!philo->data->complete && !philo->data->death_occured)
		{
			pthread_mutex_lock(philo->l_fork);
			write_request(philo, TAKE_FORKS);
		}
		else
			pthread_mutex_unlock(philo->r_fork);
	}
}

void	get_forks(t_socrates *philo)
{
	if (!philo->data->complete && !philo->data->death_occured)
	{
		if (philo->data->num_phils == 1)
		{
			pthread_mutex_lock(philo->r_fork);
			write_request(philo, TAKE_FORKS);
			ft_usleep(philo->data->time_to_die - get_time(philo->data) + 5,
				philo->data);
			pthread_mutex_unlock(philo->r_fork);
		}
		choose_fork(philo);
	}
}

void	go_sleep(t_socrates *philo)
{
	if (!philo->data->complete && !philo->data->death_occured)
	{
		write_request(philo, SLEEPING);
		ft_usleep(philo->data->time_of_sleep, philo->data);
		write_request(philo, THINKING);
	}
}

int	write_request(t_socrates *phil, char *message)
{
	pthread_mutex_lock(phil->data->lock);
	pthread_mutex_lock(phil->data->write);
	if (!phil->data->death_occured && !phil->data->complete)
	{
		printf("%lu %d %s\n", get_time(phil->data), phil->id, message);
	}
	pthread_mutex_unlock(phil->data->write);
	pthread_mutex_unlock(phil->data->lock);
	return (0);
}
