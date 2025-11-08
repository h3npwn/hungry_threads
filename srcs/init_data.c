/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:37:24 by abahja            #+#    #+#             */
/*   Updated: 2025/07/20 21:53:00 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	printf_at(t_log log, long t_id)
{
	static pthread_mutex_t	mut = PTHREAD_MUTEX_INITIALIZER;
	static char				*ptr;
	static long				*start_time;
	long					_time;

	if (log == INIT)
	{
		start_time = &(*(t_mighty_table **)ob_table())->start_time;
		ptr = "has taken a fork\0is eating\0is sleeping\0is thinking\0dead";
		return (0);
	}
	if (sim_ended(0, 0))
		return (0);
	pthread_mutex_lock(&mut);
	if (sim_ended(0, 0))
		return (pthread_mutex_unlock(&mut), 0);
	_time = get_time_in_ms() - *start_time;
	printf("%ld %ld %s\n", _time, t_id, &ptr[log]);
	pthread_mutex_unlock(&mut);
	return (0);
}

static void	*fork_treater(pthread_mutex_t *forks, t_thread *philo, int i)
{
	if (philo->id % 2)
	{
		philo->first_fork = &forks[(i + 1) % philo->n_t];
		philo->second_fork = &forks[i];
	}
	else
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % philo->n_t];
	}
	return (NULL);
}

void	assign_forks(void *memblock, t_thread *null_ptr)
{
	int				i;

	if (!memblock || !*(t_mighty_table **)memblock)
		return ;
	i = 0;
	while (i < (*(t_mighty_table **)memblock)->n_ofplayers)
	{
		null_ptr = (*(t_mighty_table **)memblock)->philo + i;
		null_ptr->id = i + 1;
		null_ptr->n_t = (*(t_mighty_table **)memblock)->n_ofplayers;
		null_ptr->start_time = &((*(t_mighty_table **)memblock)->start_time);
		null_ptr->eat_lock = &((*(t_mighty_table **)memblock)->eat_lock);
		null_ptr->last_eat = 0;
		null_ptr->t_eat = 0;
		null_ptr->max_eat = -1337;
		if ((*(t_mighty_table **)memblock)->x_lim)
			null_ptr->max_eat = (*(t_mighty_table **)memblock)->x_lim;
		null_ptr->t_todie = (*(t_mighty_table **)memblock)->t_todie;
		null_ptr->t_toeat = (*(t_mighty_table **)memblock)->t_toeat;
		null_ptr->t_tosleep = (*(t_mighty_table **)memblock)->t_tosleep;
		fork_treater((*(t_mighty_table **)memblock)->forks, null_ptr, i);
		i++;
	}
}

static void	mutex_init(void *memblock, pthread_mutex_t *mutex_block, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_mutex_init((mutex_block + i), NULL) != 0)
		{
			check_rules(memblock, 1);
			return ;
		}
		i++;
	}
	if (pthread_mutex_init(&(*(t_mighty_table **)memblock)->eat_lock, 0) != 0)
	{
		check_rules(memblock, 1);
		return ;
	}
}

void	*init_inner_alloc(void *memblock)
{
	t_mighty_table	*table;

	if (!memblock || !*(void **)memblock)
		return (NULL);
	table = *(t_mighty_table **)memblock;
	table->philo = malloc(sizeof(t_thread) * table->n_ofplayers);
	if (!table->philo)
		return (check_rules(memblock, 1), NULL);
	memset(table->philo, 0, sizeof(t_thread) * table->n_ofplayers);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_ofplayers);
	if (!table->forks)
		return (check_rules(memblock, 1), NULL);
	memset(table->forks, 0, sizeof(pthread_mutex_t) * table->n_ofplayers);
	mutex_init(memblock, table->forks, table->n_ofplayers);
	return (table);
}
