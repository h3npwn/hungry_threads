/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 08:46:40 by abahja            #+#    #+#             */
/*   Updated: 2025/07/20 20:15:24 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

int	main(int ac, char **args)
{
	t_mighty_table	*table;

	table = init_table(ac);
	init_data(&table, args);
	init_inner_alloc(&table);
	assign_forks(&table, 0);
	if (!table)
		return (1);
	*(t_mighty_table **)ob_table() = table;
	printf_at(INIT, 0);
	sim_ended(1, table);
	simulation_start(&table);
	return (0);
}
