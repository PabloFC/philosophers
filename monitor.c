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

static int	check_death(t_philo *philo)
{
	long long	t;

	pthread_mutex_lock(&philo->meal_mutex);
	t = timestamp() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (t >= philo->rules->time_to_die)
	{
		pthread_mutex_lock(&philo->rules->print_mutex);
		if (!philo->rules->died)
		{
			philo->rules->died = 1;
			printf("%lld %d died\n",
				timestamp() - philo->rules->start_time,
				philo->id);
		}
		pthread_mutex_unlock(&philo->rules->print_mutex);
		return (1);
	}
	return (0);
}

static int	all_ate_enough(t_rules *rules)
{
	int	i;
	int	done;

	i = 0;
	done = 1;
	if (rules->must_eat <= 0)
		return (0);
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->philos[i].meal_mutex);
		if (rules->philos[i].meals_eaten < rules->must_eat)
			done = 0;
		pthread_mutex_unlock(&rules->philos[i].meal_mutex);
		i++;
	}
	return (done);
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
			if (check_death(&rules->philos[i]))
				return (NULL);
			i++;
		}
		if (all_ate_enough(rules))
		{
			pthread_mutex_lock(&rules->print_mutex);
			rules->died = 1;
			pthread_mutex_unlock(&rules->print_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
