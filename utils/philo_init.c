#include "../library/philo.h"

void *Dinning_philo(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    (void)philo;
   // pthread_mutex_lock(&philo->lock);
   // pthread_mutex_unlock(&philo->lock);

    return NULL;
}

void philo_init(t_utils *utils, t_philo *philo, char **av)
{
    int i = 0;
    philo->utils = utils;
    utils->philo_num = ft_atoi(av[1]);
    utils->time_to_die = ft_atoi(av[2]);
    utils->time_to_eat = ft_atoi(av[3]);
    utils->time_to_sleep = ft_atoi(av[4]);
    utils->num_of_time_to_eat = ft_atoi(av[5]);
    utils->death_flag = 0;
    //pthread_mutex_init(&philo->lock, NULL);

    while(i < utils->philo_num)
    {
        philo[i].utils = utils;
        philo[i].id = i + 1;
        pthread_create(&philo[i].thread_id, NULL, Dinning_philo, &philo[i]);
        i++;
    }
    i = 0;
    while(i < utils->philo_num)
    {
        philo[i].id = i + 1;
        pthread_join(philo[i].thread_id, NULL);
        i++;
    }
    philo[i].id = 0;
}