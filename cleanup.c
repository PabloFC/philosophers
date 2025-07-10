/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafuente <pafuente@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:28:17 by pafuente          #+#    #+#             */
/*   Updated: 2025/07/10 10:28:17 by pafuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->print_mutex);
}

void	cleanup(t_rules *rules)
{
	if (rules->forks)
	{
		destroy_mutexes(rules);
		free(rules->forks);
		rules->forks = NULL;
	}
	if (rules->philos)
	{
		free(rules->philos);
		rules->philos = NULL;
	}
}
