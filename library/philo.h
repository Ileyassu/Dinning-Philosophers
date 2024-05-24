#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

typedef enum 
{
    EAT,
    SLEEP,
    THINK,
} state;

typedef struct s_utils
{
    long long time_start;
    int death_flag;
    int philo_num;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_of_time_to_eat;
    pthread_mutex_t	*forks;
    pthread_mutex_t meal;
    pthread_mutex_t printing;
}   t_utils;

typedef struct s_philo
{
    int	r_fork;
    int	l_fork;
    pthread_mutex_t lock;
    int eat;
    int i;
    unsigned long last_meal;
    t_utils *utils;
    state current_state;
    pthread_t thread_id;
    int id;
}   t_philo;

int	ft_isdigit(int arg);
int	ft_atoi(const char *pt);
int philo_init(t_utils *utils, t_philo *philo, char **av);
int parse(t_utils *utils, int ac, char **av);
size_t get_time();
void philo_died (t_philo *philo);
void philo_eating(t_philo *philo);
void philo_sleeping(t_philo *philo);

#endif