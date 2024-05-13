#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_utils
{
    int death_flag;
    int philo_num;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_of_time_to_eat;
}   t_utils;

typedef struct s_philo
{
    pthread_mutex_t	r_fork;
	pthread_mutex_t	l_fork;
    pthread_mutex_t lock;
    int eat;
    int i;
    t_utils *utils;
    pthread_t thread_id;
    int id;
}   t_philo;

int	ft_isdigit(int arg);
int	ft_atoi(const char *pt);
void philo_init(t_utils *utils, t_philo *philo, char **av);
int parse(t_utils *utils, int ac, char **av);

#endif