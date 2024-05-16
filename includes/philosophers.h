/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:35:07 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/16 19:59:02 by fcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdint.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>
# include <bits/types/struct_timeval.h>
# include <sys/types.h>

# define ALLOC_ERR_1 "ERROR WHILE ALLOCATING THREADS IDs"
# define ALLOC_ERR_3 "ERROR WHILE ALLOCATING PHILOS"
# define ALLOC_ERR_2 "ERROR WHILE ALLOCATING FORKS"
//	input_err
# define ERR_IN_1 "INVALID INPUT CHARACTER"
# define ERR_IN_2 "INVALID INPUT VALUES"
//	pthread_err
# define TH_ERR "ERROR WHILE CREATING THREADS"
# define JOIN_ERR "ERROR WHILE JOINING THREADS"
# define INIT_ERR_1 "ERROR WHILE INIT FORKS"
//	time_err
# define TIME_ERR "UNABLE TO RETRIVE UTC"
//	philo_msg
# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

# define HALFBURGER "has picked up half of a double cheeseburger"
# define OHALFBURGER "has picked up the other half of a double cheeseburger"
# define EATBURGER "has begun eating double cheeseburger number "
# define FATDEATH "could not munch fast enough..."
# define DROPHALF "has disassembled the top half of his double cheeseburger"
# define DROPOHALF "has disassembled the bottom half of his double cheeseburger"
# define NAP "has decided its time for a nap"
# define WOKE "has decided its time to wake up"

typedef struct s_socrates
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	uint64_t		timeToDie;
	uint64_t		mealStart;
	int				status;
	int				eating;
	int				fattyFactor;
	pthread_mutex_t	*rFork;
	pthread_mutex_t	*lFork;
}	t_socrates;

typedef struct s_data
{
	pthread_t		*tid;
	int				numPhils;
	int				numTimesPhilMustEat;
	int				deathOccured;
	int				complete;
	t_socrates		*philes;
	int				fattyCount;
	uint64_t		timeOfEat;
	uint64_t		timeOfSleep;
	uint64_t		timeOfStart;
	uint64_t		timeToDie;
	pthread_mutex_t	*forks;
	// pthread_mutex_t	lock;
	pthread_mutex_t	*write;
}	t_data;

void		ft_exit(t_data *data);
void		eat(t_socrates *philo);
void		get_forks(t_socrates *philo);
void		go_sleep(t_socrates *philo);
void		messages(char *str, t_socrates *philo);
int			thread_init(t_data *data);
void		set_em_up(int argc, char *argv[], t_data *data);
int			enableThinking(t_data *data);
int			initForks(t_data *data);
int			error(char *str, t_data *data);
u_int64_t	get_time(t_data *data);
int			ft_usleep(useconds_t time, t_data *data);
int			mallocationStation(t_data *data);
void		announce_death(t_socrates *phil, int id);
int			write_request(t_socrates *phil, char *message);

#endif // !PHILOSOPHERS_H
