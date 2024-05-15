/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:34:20 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/14 19:12:19 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char *argv[])
{
	t_data data;
	set_em_up(argc, argv, &data);
	if (thread_init(&data))
		return(1);
	ft_exit(&data);
	return (0);
}
