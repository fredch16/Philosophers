/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:35:07 by fcharbon          #+#    #+#             */
/*   Updated: 2024/05/17 20:02:04 by fcharbon         ###   ########.fr       */
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

# define USAGE "BING BONG\n"

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
	uint64_t		time_to_die;
	uint64_t		meal_start;
	int				status;
	int				eating;
	int				fatty_factor;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_socrates;

typedef struct s_data
{
	pthread_t		*tid;
	int				num_phils;
	int				eat_goal;
	int				death_occured;
	int				complete;
	t_socrates		*philes;
	int				fatty_count;
	uint64_t		time_of_eat;
	uint64_t		time_of_sleep;
	uint64_t		time_of_start;
	uint64_t		time_to_die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*write;
}	t_data;

void		ft_exit(t_data *data);
void		eat(t_socrates *philo);
void		get_forks(t_socrates *philo);
void		go_sleep(t_socrates *philo);
void		messages(char *str, t_socrates *philo);
int			thread_init(t_data *data);
void		set_em_up(int argc, char *argv[], t_data *data);
int			enable_thinking(t_data *data);
int			init_forks(t_data *data);
int			error(char *str, t_data *data);
u_int64_t	get_time(t_data *data);
int			supa_thread_init(t_data *data);
int			check_stop_condition(t_socrates *numba1, int i);
int			ft_usleep(useconds_t time, t_data *data);
int			mallocation_station(t_data *data);
void		announce_death(t_socrates *phil, int id);
int			write_request(t_socrates *phil, char *message);

#endif // !PHILOSOPHERS_H
