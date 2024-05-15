/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:54:20 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/01 18:40:25 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <pthread.h>

int	mails = 0;
pthread_mutex_t mutex;

void*	routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	(void)argv;
	(void)argc;

	pthread_t th[4];
	pthread_mutex_init(&mutex, NULL);
	
	int	i;

	i = 0;
	while (i < 4)
	{
		if (pthread_create(th + i, NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread\n");
			return (-2);
		}
		printf("Thread %d has been created\n", i);

	i++;
	}
	i = 0;
	while (i < 4)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (5);
		printf("Thread %d has finished\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails in the mailbox: %d\n", mails);

	return (0);
}
