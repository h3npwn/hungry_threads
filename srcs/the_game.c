/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:11:22 by abahja            #+#    #+#             */
/*   Updated: 2025/07/30 11:08:33 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	eat_sleep(t_thread *p)
{
	pthread_mutex_lock(p->first_fork);
	printf_at(TAKE, p->id);
	pthread_mutex_lock(p->second_fork);
	printf_at(TAKE, p->id);
	printf_at(EAT, p->id);
	pthread_mutex_lock(p->eat_lock);
	p->last_eat = get_time_in_ms();
	if (p->max_eat != -1337)
		p->t_eat++;
	pthread_mutex_unlock(p->eat_lock);
	ft_usleep(p->t_toeat);
	pthread_mutex_unlock(p->second_fork);
	pthread_mutex_unlock(p->first_fork);
	printf_at(SLEEP, p->id);
	ft_usleep(p->t_tosleep);
}

static void	think_routine(t_thread *philo)
{
	time_t	time;

	printf_at(THINK, philo->id);
	time = (philo->t_todie - (get_time_in_ms() - philo->last_eat)
			- philo->t_toeat);
	if (time >= 600)
		time = 200;
	if (time < 0)
		return ;
	ft_usleep(time);
}

void	*routine(void *philo)
{
	t_thread		*phil;
	t_mighty_table	*table;

	phil = philo;
	table = *(void **)ob_table();
	pthread_mutex_lock(phil->eat_lock);
	phil->last_eat = (table->start_time);
	pthread_mutex_unlock(phil->eat_lock);
	delay(table->start_time);
	if (phil->n_t == 1)
	{
		printf_at(TAKE, 1);
		return (ft_usleep(phil->t_todie), NULL);
	}
	if (phil->id % 2)
	{
		printf_at(THINK, phil->id);
		ft_usleep(1);
	}
	while (!sim_ended(0, 0))
	{
		eat_sleep((t_thread *)philo);
		think_routine(philo);
	}
	return (NULL);
}

void	destroy(t_mighty_table *table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	while (i < table->n_ofplayers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->eat_lock);
	if (table->forks)
		free(table->forks);
	if (table->philo)
		free(table->philo);
	free(table);
}

void	simulation_start(t_mighty_table **tablex)
{
	int				i;
	t_mighty_table	*table;
	pthread_t		chinigami;

	i = 0;
	table = *tablex;
	if (table->n_ofplayers == 0 && (destroy(table), 1))
		return ;
	table->start_time = get_time_in_ms() + (table->n_ofplayers * 2);
	while (i < table->n_ofplayers)
	{
		pthread_create(&table->philo[i].r_id, 0, routine, &table->philo[i]);
		i++;
	}
	pthread_create(&chinigami, NULL, monitor, table);
	i = 0;
	while (i < table->n_ofplayers)
	{
		pthread_join(table->philo[i].r_id, NULL);
		i++;
	}
	pthread_join(chinigami, NULL);
	destroy(table);
}
