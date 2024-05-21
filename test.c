#include<pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_utils
{
    pthread_mutex_t forks;
    int philo_num;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_limit_eat;
    int died;
}   t_utils;

typedef struct s_philo
{
    pthread_t threads;
    int id;
    int f_fork;
    int s_fork;
    size_t last_meal;
    t_utils utils;
} t_philo;

size_t get_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void philo_died (t_philo *philo)
{
    printf("philo %d died\n", philo->id);
}
void phil_eating(t_philo *philo)
{
    size_t start_time = get_time();
    philo->last_meal = start_time;
    while(get_time() - start_time < philo->utils.time_to_eat)
        usleep(100);
    usleep(2000);
}
void phil_sleeping(t_philo *philo)
{
    size_t start_time = get_time();
    while(get_time() - start_time < philo->utils.time_to_sleep)
    {
        usleep(100);
    }
}
pthread_mutex_t mutex;
int what = 0;

void *something(void *philo)
{
    t_philo *p = philo;
    if (p->id % 2 == 0)
    {
        usleep(40000);
    }
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&p->utils.forks);
    printf("philo %d took first fork %d\n", p->id, p->f_fork);
    printf("philo %d took second fork %d\n", p->id, p->s_fork);
    printf("philo %d is eating\n", p->id);
    phil_eating(p);
    pthread_mutex_unlock(&mutex);
    printf("philo %d is sleeping\n", p->id);
    phil_sleeping(philo);
    printf("philo %d is thinking\n", p->id);
    return NULL;
}
int main(int ac, char **av)
{
    t_philo *philo;
    t_utils utils;

    pthread_mutex_init(&utils.forks, NULL);
    pthread_mutex_init(&mutex, NULL);
    utils.philo_num = atoi(av[1]);
    utils.time_to_die = atoi(av[2]);
    utils.time_to_eat = atoi(av[3]);
    utils.time_to_sleep = atoi(av[4]);

    philo = malloc(sizeof(utils.philo_num));
    int i = 0;
    while(i < utils.philo_num)
    {
        philo[i].id = i + 1;
        philo[i].f_fork = i + 1;
        philo[i].s_fork = (i + 1) % utils.philo_num + 1;
        philo[i].utils = utils;
        pthread_create(&philo[i].threads, NULL, &something, &philo[i]);
        i++;
    }

    i = 0;
    while(i < utils.philo_num)
    {
        pthread_join(philo[i].threads, NULL);
        i++;
    }
}
