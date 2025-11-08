/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:37:21 by abahja            #+#    #+#             */
/*   Updated: 2025/07/30 10:41:02 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ft_atoi(const char *str, int *check, void *which)
{
	int			i;
	long		result;

	i = 0x0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (++(*check), 0);
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (++(*check), 0);
		i++;
	}
	if (str[i] != '\0')
		return (++(*check), 0);
	if ((which == check && result < 60) || (which != check && result == 0))
		return (++(*check), 0);
	return ((int)(result));
}

static void	*error_handle(t_error error)
{
	if (error == init)
	{
		write(2, "usage : ./philo {num_players}", 30);
		write(2, "{TimeToDie}{TimeToEat}", 23);
		write(2, "{TimeToSleep}[limited eat]\n", 27);
	}
	if (error == malloc_fail)
		write(2, "memory error\n", 14);
	if (error == rule_error)
		write(2, "Error During Init Values*-*\n", 29);
	return (NULL);
}

t_mighty_table	*init_table(int ac)
{
	char			lim;
	t_mighty_table	*table;

	table = 0x0;
	lim = 0x0;
	if (ac != 5 && (++lim && ac != 6))
		return (error_handle(init));
	table = malloc(sizeof(t_mighty_table));
	if (!table)
		return (error_handle(malloc_fail));
	memset(table, 0x0, sizeof(t_mighty_table));
	table->x_lim = lim;
	return (table);
}

void	check_rules(void *memblock, char check)
{
	if (check == 0)
		return ;
	if ((*(t_mighty_table **)memblock)->philo)
		free((*(t_mighty_table **)memblock)->philo);
	if ((*(t_mighty_table **)memblock)->forks)
		free((*(t_mighty_table **)memblock)->forks);
	free(*(t_mighty_table **)memblock);
	*(t_mighty_table **)memblock = error_handle(rule_error);
}

void	init_data(void *memblock, char **av)
{
	t_mighty_table	*table;
	int				check_t;
	int				check_v;

	if (!memblock || !*(void **)memblock)
		return ;
	check_t = 0;
	check_v = 0;
	table = *(t_mighty_table **)memblock;
	table->n_ofplayers = ft_atoi(av[1], &check_v, &check_t);
	table->t_todie = ft_atoi(av[2], &check_t, &check_t);
	table->t_toeat = ft_atoi(av[3], &check_t, &check_t);
	table->t_tosleep = ft_atoi(av[4], &check_t, &check_t);
	if (table->x_lim)
		table->x_lim = ft_atoi(av[5], &check_v, &check_t);
	check_t += check_v;
	check_rules(memblock, check_t);
}
