/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:50:02 by abahja            #+#    #+#             */
/*   Updated: 2025/07/30 11:13:09 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	check_if_dead(t_thread *philos)
{
	int				i;
	t_mighty_table	*table;
	t_thread		*p;

	i = 0;
	table = *(void **)ob_table();
	pthread_mutex_lock(&table->eat_lock);
	while (i < table->n_ofplayers)
	{
		p = philos + i;
		if (get_time_in_ms() - p->last_eat >= p->t_todie)
		{
			printf_at(DEAD, p->id);
			set_value(1);
			return (pthread_mutex_unlock(p->eat_lock), 1);
		}
		i++;
	}
	pthread_mutex_unlock(&table->eat_lock);
	return (0);
}

static int	check_if_eat(t_thread *philos)
{
	int				i;
	char			flag;
	t_mighty_table	*table;
	t_thread		*p;

	flag = 1;
	i = 0;
	table = *(void **)ob_table();
	pthread_mutex_lock(&table->eat_lock);
	while (i < table->n_ofplayers)
	{
		p = philos + i;
		if (p->t_eat < p->max_eat)
		{
			flag = 0;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&table->eat_lock);
	if (flag)
		set_value(1);
	return (flag);
}

void	delay(time_t ts)
{
	while (get_time_in_ms() < ts)
		continue ;
}

void	*monitor(void *tablex)
{
	t_mighty_table	*table;

	table = tablex;
	delay(table->start_time);
	while (1)
	{
		if ((table->x_lim && check_if_eat(table->philo))
			|| check_if_dead(table->philo))
			break ;
		usleep(500);
	}
	return (tablex);
}
