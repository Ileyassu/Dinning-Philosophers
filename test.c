#include<pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t lock;
typedef struct s_utils
{
    // pthread_mutex_t lock;
    int i;
} t_utils;
typedef struct s_philo
{
    pthread_t threads;
    int id;
    pthread_mutex_t lock;
    t_utils *utils;
} t_philo;

void *testing(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->lock);
    philo->utils->i += philo->id;
    pthread_mutex_unlock(&philo->lock);
    return NULL;
}

int main(int ac, char **av)
{
    t_philo philo[3];
    t_utils utils;
    utils.i = 0;

    int i = 0;

    pthread_mutex_init(&lock, NULL);
    while(i < 3)
    {
        philo[i].id = i;
        philo[i].utils = &utils;
        pthread_mutex_init(&philo[i].lock, NULL);
        pthread_create(&philo[i].threads, NULL, &testing, &philo[i]);
        usleep(100);
        i++;
    }
    i = 0;
    while(i < 3)
    {
        pthread_join(philo[i].threads, NULL);
        i++;
    }
    i = 0;
    while(i < 3)
    {
        printf("philo[%d].utils->i = %d\n", i, philo[i].utils->i);
        i++;
    }
    return 0;
}
