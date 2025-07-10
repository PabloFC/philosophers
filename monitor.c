/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafuente <pafuente@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:29:04 by pafuente          #+#    #+#             */
/*   Updated: 2025/07/10 10:29:04 by pafuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_ate_enough(t_rules *rules)
{
	int	i;

	if (rules->must_eat <= 0)
		return (0);
	i = 0;
	while (i < rules->nb_philo)
	{
		if (rules->philos[i].meals_eaten < rules->must_eat)
			return (0);
		i++;
	}
	return (1);
}

static int	check_death(t_rules *rules, int i)
{
	long long	time;

	time = timestamp();
	if ((time - rules->philos[i].last_meal) > rules->time_to_die)
	{
		pthread_mutex_lock(&rules->print_mutex);
		if (!rules->died)
		{
			rules->died = 1;
			printf("%lld %d died\n",
				time - rules->start_time,
				rules->philos[i].id);
		}
		pthread_mutex_unlock(&rules->print_mutex);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	while (!rules->died)
	{
		i = 0;
		while (i < rules->nb_philo)
		{
			if (check_death(rules, i))
				return (NULL);
			i++;
		}
		if (all_ate_enough(rules))
		{
			rules->died = 1;
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
