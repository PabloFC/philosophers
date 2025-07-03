#include "philo.h"

static void destroy_mutexes(t_rules *rules)
{
    int i;

    i = 0;
    while (i < rules->nb_philo)
    {
        pthread_mutex_destroy(&rules->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&rules->print_mutex);
}

void cleanup(t_rules *rules)
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
