#include "../library/philo.h"

void *thread_test(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    (void)philo;
    //printf("test");
    printf("id = %d\n", philo->id);
    return NULL;
}

void philo_init(t_utils *utils, t_philo *philo, char **av)
{
    int i = 0;
    utils->philo_num = ft_atoi(av[1]);
    utils->time_to_die = ft_atoi(av[2]);
    utils->time_to_eat = ft_atoi(av[3]);
    utils->time_to_sleep = ft_atoi(av[4]);
    utils->num_of_time_to_eat = ft_atoi(av[5]);

    while(i < utils->philo_num)
    {
        philo[i].id = i + 1;
        pthread_create(&philo[i].thread_id, NULL, thread_test, &philo[i]);
        pthread_join(philo[i].thread_id, NULL);
        //printf("i = %d\n", i);
        i++;
    }
}