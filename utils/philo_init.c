#include "../library/philo.h"

pthread_mutex_t order_mutex = PTHREAD_MUTEX_INITIALIZER;
int current_philo = 0;

int monitoring_philo(t_philo *philo)
{
    int i;
    while(philo->utils->death_flag != 1)
    {
        i = 0;
        while(i < philo->utils->philo_num)
        {
            pthread_mutex_lock(&philo->utils->meal);
            if (get_time() - philo->last_meal > (unsigned long)philo->utils->time_to_die)
            {
                philo->utils->death_flag = 1;
                pthread_mutex_unlock(&philo->utils->meal);
                printf("---- philo->utils->time_start %lld ------ philo->last_meal %lu\n", philo->utils->time_start, philo->last_meal);
                printf("%llu %d  died\n", get_time() - philo->utils->time_start, philo->id);
                return(1);
            }
            pthread_mutex_unlock(&philo->utils->meal);
            i++;
        }
          usleep(100);
    }
    return (0);
}

void *Dinning_philo(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    (void)philo;
        if (philo->id % 2 == 0)
        {
            usleep(150);
        }
    while(philo->utils->death_flag != 1)
    {
        pthread_mutex_lock(&philo->utils->forks[philo->r_fork]);
        printf("%llu %d has taken a fork\n", get_time() - philo->utils->time_start, philo->id);
        pthread_mutex_lock(&philo->utils->forks[philo->l_fork]);
        printf("%llu %d has taken a fork\n", get_time() - philo->utils->time_start, philo->id);
        philo_eating(philo);
        printf("%llu %d is eating\n", get_time() - philo->utils->time_start, philo->id);
        // pthread_mutex_lock(&philo->utils->meal);
        // philo->last_meal = get_time();
        // pthread_mutex_unlock(&philo->utils->meal);
        pthread_mutex_unlock(&philo->utils->forks[philo->r_fork]);
        pthread_mutex_unlock(&philo->utils->forks[philo->l_fork]);
        printf("%llu %d is sleeping\n", get_time() - philo->utils->time_start, philo->id);
        philo_sleeping(philo);
        printf("%llu %d is thinking\n", get_time() - philo->utils->time_start, philo->id);
    }

    return NULL;
}

int philo_init(t_utils *utils, t_philo *philo, char **av)
{
    int i = -1;
    philo->utils = utils;
    utils->philo_num = ft_atoi(av[1]);
    utils->time_to_die = ft_atoi(av[2]);
    utils->time_to_eat = ft_atoi(av[3]);
    utils->time_to_sleep = ft_atoi(av[4]);
    utils->death_flag = 0;
    utils->num_of_time_to_eat = ft_atoi(av[5]);
    utils->forks = malloc(sizeof(pthread_mutex_t) * utils->philo_num);
    //update philo time after eating
    pthread_mutex_init(&utils->meal, NULL);
    // pthread_mutex_init(&philo->lock, NULL);
    while(++i < utils->philo_num)
    
    {
        philo[i].eat = utils->num_of_time_to_eat;
        philo[i].utils = utils;
        philo[i].id = i + 1;
        philo[i].r_fork = i;
        philo[i].l_fork = (i + 1) % utils->philo_num;
        pthread_mutex_init(&utils->forks[i], NULL);
    }
    i = -1;
    utils->time_start = get_time();
    while (++i < utils->philo_num)
    {
        philo[i].last_meal = get_time();
        pthread_create(&philo[i].thread_id, NULL, Dinning_philo, &philo[i]);
        usleep(100);
    }
    if (monitoring_philo(philo))
    {
        return (1);
    }
    i = 0;
    while(i < utils->philo_num)
    {
        pthread_join(philo[i].thread_id, NULL);
        i++;
    }
    return 0;
}