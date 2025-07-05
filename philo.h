#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_rules t_rules;

typedef struct s_philo
{
    int id;
    int meals_eaten;
    long long last_meal;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_rules *rules;
} t_philo;

struct s_rules
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    int died;
    long long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    t_philo *philos;
};

int init_all(t_rules *rules, int argc, char **argv);
int start_simulation(t_rules *rules);
void *routine(void *arg);
void *monitor(void *arg);
void print_status(t_philo *philo, char *status);
void ft_usleep(int ms);
long long timestamp(void);
int ft_atoi(const char *str);
void cleanup(t_rules *rules);

#endif
