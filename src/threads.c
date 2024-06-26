/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:32:05 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/17 20:12:08 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *fakephilo)
{
	t_socrates	*philo;

	philo = (t_socrates *)fakephilo;
	pthread_mutex_lock(philo->data->lock);
	while (!philo->data->complete && !philo->data->death_occured)
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

int	check_stop_conditions(t_socrates *numba1, int i)
{
	t_socrates	*numba1;
	int			i;

	i = 0;
	numba1 = (t_socrates *)fake;
	pthread_mutex_lock(numba1->data->lock);
	while (!numba1->data->complete && !numba1->data->death_occured)
	{
		pthread_mutex_unlock(numba1->data->lock);
		i = 0;
		if (!check_stop_condition(numba1, i))
			return (NULL);
		pthread_mutex_lock(numba1->data->lock);
	}
	pthread_mutex_unlock(numba1->data->lock);
	return (NULL);
}

int	check_stop_condition(t_socrates *numba1, int i)
{
	while (!numba1->data->death_occured && i < numba1->data->num_phils)
	{
		pthread_mutex_lock(numba1->data->lock);
		if (get_time(numba1->data) - numba1->data->philes[i].meal_start
			> numba1->data->time_to_die)
		{
			announce_death(numba1, i + 1);
			pthread_mutex_unlock(numba1->data->lock);
			return (0);
		}
		else if (numba1->data->fatty_count == numba1->data->num_phils)
		{
			numba1->data->complete = 1;
			pthread_mutex_unlock(numba1->data->lock);
			return (0);
		}
		pthread_mutex_unlock(numba1->data->lock);
		i++;
	}
	return (1);
}

int	thread_init(t_data *data)
{
	int				i;
	pthread_t		t0;

	i = 0;
	if (data->eat_goal > 0)
	{
		if (pthread_create(&t0, NULL, &supervisor, &data->philes[0]))
			return (error(TH_ERR, data));
	}
	if (pthread_join(t0, NULL))
	{
		return (error(JOIN_ERR, data));
	}
	while (i < data->num_phils)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philes[i]))
			return (error(TH_ERR, data));
		i++;
	}
	if (thread_join(data, t0))
		return (error(JOIN_ERR, data));
	return (0);
}

int	thread_join(t_data *data, pthread_t t0)
{
	int	i;

	i = 0;
	if (pthread_join(t0, NULL))
	{
		return (error(JOIN_ERR, data));
	}
	while (i < data->num_phils)
	{
		if (pthread_join(data->tid[i], NULL))
			return (error(JOIN_ERR, data));
		i++;
	}
	ft_exit(data);
	return (0);
}
