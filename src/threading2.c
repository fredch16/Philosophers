/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:43:18 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/01 22:41:21 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

void* roll_dice() {
	int	value = (rand() % 6) + 1;
	int	*result = malloc(sizeof(int));
	*result = value;
	// printf("%d\n", value);
	printf("Thread result: %p\n", result);
	return ((void*)result);
}
int	main(int argc, char* argv[]) {
	int	*res;

	srand(time(NULL));
	pthread_t th;
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0) {
		return 1;
	}
	if (pthread_join(th, (void**)&res) != 0) {
		return 2;
	}
	printf("Result: %d\n", *res);
	printf("Main result: %p\n", res);
	free(res);
	return 0;
}
