/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafuente <pafuente@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:20:21 by pafuente          #+#    #+#             */
/*   Updated: 2025/07/10 11:20:21 by pafuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

struct	s_rules;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	struct s_rules	*rules;
}	t_philo;

typedef struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				died;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
}	t_rules;

int			init_all(t_rules *rules, int argc, char **argv);
int			start_simulation(t_rules *rules);
int			philo_sleep_think(t_philo *philo);
void		*routine(void *arg);
void		*monitor(void *arg);
void		print_status(t_philo *philo, char *status);
void		ft_usleep(int ms);
long long	timestamp(void);
int			ft_atoi(const char *str);
void		cleanup(t_rules *rules);

#endif
