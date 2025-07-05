#include "philo.h"

void print_status(t_philo *philo, char *status)
{
    pthread_mutex_lock(&philo->rules->print_mutex);
    if (!philo->rules->died)
        printf("%lld %d %s\n", timestamp() - philo->rules->start_time,
               philo->id, status);
    pthread_mutex_unlock(&philo->rules->print_mutex);
}

static void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "has taken a fork");

    pthread_mutex_lock(philo->right_fork);
    print_status(philo, "has taken a fork");

    print_status(philo, "is eating");
    philo->last_meal = timestamp();
    philo->meals_eaten++;

    ft_usleep(philo->rules->time_to_eat);

    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
        usleep(1000);

    while (!philo->rules->died)
    {
        eat(philo);
        if (philo->rules->must_eat > 0 &&
            philo->meals_eaten >= philo->rules->must_eat)
            break;
        print_status(philo, "is sleeping");
        ft_usleep(philo->rules->time_to_sleep);
        print_status(philo, "is thinking");
    }
    return (NULL);
}
