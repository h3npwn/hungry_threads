/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:59:41 by abahja            #+#    #+#             */
/*   Updated: 2025/07/20 21:30:52 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

time_t	get_time_in_ms(void)
{
	t_ms	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(time_t ts)
{
	time_t	tsx;

	tsx = get_time_in_ms();
	while (get_time_in_ms() - tsx < ts && sim_ended(0, 0) == false)
		usleep(500);
}

void	*set_value(bool value)
{
	static t_mighty_table	*table = NULL;
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	static int				init = 1;

	if (init == 1)
	{
		table = *(void **)ob_table();
		return (init--, &lock);
	}
	pthread_mutex_lock(&lock);
	table->s_fin = value;
	pthread_mutex_unlock(&lock);
	return (NULL);
}

void	*ob_table(void)
{
	static t_mighty_table	*table = NULL;

	return (&table);
}

bool	sim_ended(bool init, void *ptr)
{
	bool					ret;
	static t_mighty_table	*table;
	static pthread_mutex_t	*lock_ptr;

	if (init == true)
	{
		lock_ptr = (pthread_mutex_t *)set_value(false);
		table = ptr;
		return (false);
	}
	ret = false;
	pthread_mutex_lock(lock_ptr);
	if (table->s_fin == true)
	{
		ret = true;
	}
	pthread_mutex_unlock(lock_ptr);
	return (ret);
}
