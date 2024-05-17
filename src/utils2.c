/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:51:23 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/17 19:52:04 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	announce_death(t_socrates *phil, int id)
{
	printf("%lu %d died\n", get_time(phil->data), id);
	phil->data->death_occured = 1;
}
