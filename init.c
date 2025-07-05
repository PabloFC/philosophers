#include "philo.h"

static int init_mutexes(t_rules *rules)
{
    int i;

    rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
    if (!rules->forks)
        return (1);
    i = 0;
    while (i < rules->nb_philo)
    {
        if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
            return (1);
        i++;
    }
    if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
        return (1);
    return (0);
}

static int init_philos(t_rules *rules)
{
    int i;

    rules->philos = malloc(sizeof(t_philo) * rules->nb_philo);
    if (!rules->philos)
        return (1);
    i = 0;
    while (i < rules->nb_philo)
    {
        rules->philos[i].id = i + 1;
        rules->philos[i].meals_eaten = 0;
        rules->philos[i].last_meal = 0;
        rules->philos[i].left_fork = &rules->forks[i];
        rules->philos[i].right_fork = &rules->forks[(i + 1) % rules->nb_philo];
        rules->philos[i].rules = rules;
        i++;
    }
    return (0);
}

static int	parse_args(t_rules *rules, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->must_eat = ft_atoi(argv[5]);
	else
		rules->must_eat = -1;
	if (rules->nb_philo <= 0
		|| rules->time_to_die <= 0
		|| rules->time_to_eat <= 0
		|| rules->time_to_sleep <= 0)
		return (1);
	if (argc == 6 && rules->must_eat <= 0)
		return (1);
	rules->died = 0;
	return (0);
}

int init_all(t_rules *rules, int argc, char **argv)
{
    if (parse_args(rules, argc, argv))
        return (printf("Error: invalid arguments\n"), 1);
    if (init_mutexes(rules))
        return (printf("Error: failed to initialize mutexes\n"), 1);
    if (init_philos(rules))
        return (printf("Error: failed to initialize philosophers\n"), 1);
    rules->start_time = timestamp();
    return (0);
}
