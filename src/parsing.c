/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:21:47 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/17 17:50:29 by fcharbon         ###   ########.fr       */
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
		printf("Incorrect Arguments\nCorrect Usage:\n");
		printf("%s %s", USAGE1, USAGE2);
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

void	init_info(t_data *data, char *argv[], int argc)
{
	data->num_phils = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_of_eat = ft_atol(argv[3]);
	data->time_of_sleep = ft_atol(argv[4]);
	data->death_occured = 1;
	data->fatty_count = 0;
	if (argc == 6)
		data->fat_target = ft_atol(argv[5]);
	else
		data->fat_target = 9999999;
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
		init_info(data, argv, argc);
		mallocation_station(data);
		init_forks(data);
		enable_thinking(data);
	}
}
