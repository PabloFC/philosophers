/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafuente <pafuente@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:29:27 by pafuente          #+#    #+#             */
/*   Updated: 2025/07/10 10:29:27 by pafuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philos[i].last_meal = rules->start_time;
		if (pthread_create(&rules->philos[i].thread, NULL,
				routine, &rules->philos[i]) != 0)
		{
			printf("Error: Failed to create philosopher thread %d\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	join_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_join(rules->philos[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_rules *rules)
{
	pthread_t	monitor_thread;

	rules->start_time = timestamp();
	if (create_threads(rules))
		return (1);
	if (pthread_create(&monitor_thread, NULL, monitor, rules) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		return (1);
	}
	pthread_join(monitor_thread, NULL);
	join_threads(rules);
	return (0);
}
