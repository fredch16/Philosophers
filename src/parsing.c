/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:21:47 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/13 18:14:50 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <stdlib.h>

long	ft_atol(const char *nptr)
{
	long	result;
	long	sign;

	sign = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}

int	is_valid_number(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (!(*str <= '9' && *str >= '0'))
			return (0);
		str++;
	}
	return (1);
}

int	saul_goodman(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Incorrect Arguments\nCorrect Usage:\n.");
		printf("./philo <numPhils> <timeToDie> <timeToEat> <timeToSleep> <[numTimesPhilMustEat]>\n");
		exit(EXIT_FAILURE);
	}
	if (ft_atol(argv[1]) < 1)
	{
		printf("Sorry mate, you actually need philosophers to do this...\n");
		return (-2);
	}
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			printf("Sorry mate, the data you have entered is invalid...\n");
			return (-1);
		}
		i++;
	}
	return (1);
}

void	initInfo(t_data *data, char *argv[], int argc)
{
	data->numPhils = ft_atol(argv[1]);
	data->timeToDie = ft_atol(argv[2]);
	data->timeOfEat = ft_atol(argv[3]);
	data->timeOfSleep = ft_atol(argv[4]);
	data->deathOccured = 1;
	data->fattyCount = 0;
	// pthread_mutex_init(&data->write, NULL);
	// pthread_mutex_init(&data->lock, NULL);
	if (argc == 6)
		data->numTimesPhilMustEat = ft_atol(argv[5]);
}

void	set_em_up(int argc, char *argv[], t_data *data)
{
	if (saul_goodman(argc, argv) != 1)
	{
		printf("Aye man shit is NOT okay\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		initInfo(data, argv, argc);
		mallocationStation(data);
		initForks(data);
		enableThinking(data);
	}
}
