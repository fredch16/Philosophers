/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:56:54 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/13 15:42:21 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philosophers.h"
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
	int	prime = *(int*)arg;
	printf("%d ", prime);
	return (0);
	free(arg);
}

int	main(int argc, char *argv[]){
	pthread_t th[10];
	int i;
	for (int i = 0; i < 10; i++){
		int	*a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, &primes[i]) != 0)
		{
			perror("Failed to create thread\n");
		}
	}

	for (int i = 0; i < 10; i++){
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread\n");
		}
	}
	return (0);
}
