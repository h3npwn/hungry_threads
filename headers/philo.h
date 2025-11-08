/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 08:46:55 by abahja            #+#    #+#             */
/*   Updated: 2025/07/30 10:39:39 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdatomic.h>
# include <pthread.h>
# include <string.h>
# include <limits.h>
# include <sys/wait.h>
# include <stdbool.h>

typedef struct timeval		t_ms;
typedef struct s_mighty		t_mighty_table;

typedef struct s_deadly_thread
{
	unsigned int		n_t;
	atomic_int			id;
	pthread_t			r_id;
	time_t				t_start;
	time_t				t_todie;
	time_t				t_toeat;
	time_t				t_tosleep;
	time_t				last_eat;
	long				max_eat;
	long				t_eat;
	atomic_char			is_eating;
	long				*start_time;
	pthread_mutex_t		*eat_lock;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	t_mighty_table		*tab;
}	t_thread;

struct s_mighty
{
	atomic_int			n_ofplayers;
	bool				s_fin;
	long				start_time;
	long int			t_todie;
	long int			t_toeat;
	long int			t_tosleep;
	long int			x_lim;
	pthread_mutex_t		*forks;
	pthread_mutex_t		eat_lock;
	t_thread			*philo;
};

typedef enum e_etype
{
	init,
	malloc_fail,
	rule_error,
}	t_error;

typedef enum e_log
{
	TAKE = 0,
	EAT = 17,
	SLEEP = 27,
	THINK = 39,
	DEAD = 51,
	READ = 137,
	INIT,
}	t_log;

int				ft_atoi(const char *str, int *check, void *which);
t_mighty_table	*init_table(int ac);
void			init_data(void *memblock, char **av);
void			check_rules(void *memblock, char check);
void			*init_inner_alloc(void *memblock);
void			assign_forks(void *memblock, t_thread *null_ptr);
void			simulation_start(t_mighty_table **table);
int				printf_at(t_log log, long t_id);
void			ft_usleep(time_t ts);
time_t			get_time_in_ms(void);
void			*chinigami_k(void *inject);
void			waix(time_t start_time);
void			*set_value(bool value);
bool			sim_ended(bool init, void *table);
void			*ob_table(void);
void			delay(time_t ts);
void			death_m(t_mighty_table *table);
void			*monitor(void *philo);
void			destroy(t_mighty_table *table);

#endif
