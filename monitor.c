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
	long long	time;

	pthread_mutex_lock(&philo->meal_mutex);
	time = timestamp() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time >= philo->rules->time_to_die)
		return (1);
	return (0);
}

static int	all_ate_enough(t_rules *rules)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->philos[i].meal_mutex);
		if (rules->philos[i].meals_eaten >= rules->must_eat)
			count++;
		pthread_mutex_unlock(&rules->philos[i].meal_mutex);
		i++;
	}
	return (rules->must_eat > 0 && count == rules->nb_philo);
}

static void	handle_death(t_rules *rules, int i)
{
	pthread_mutex_lock(&rules->death_mutex);
	if (!rules->died)
	{
		rules->died = 1;
		pthread_mutex_lock(&rules->print_mutex);
		printf("%lld %d died\n",
			timestamp() - rules->start_time, rules->philos[i].id);
		pthread_mutex_unlock(&rules->print_mutex);
	}
	pthread_mutex_unlock(&rules->death_mutex);
}

void	*monitor(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	while (1)
	{
		i = 0;
		while (i < rules->nb_philo)
		{
			if (check_death(&rules->philos[i]))
				return (handle_death(rules, i), NULL);
			i++;
		}
		if (all_ate_enough(rules))
			return (NULL);
		usleep(1000);
	}
}
