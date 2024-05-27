#include "../library/philo.h"

int drop_forks(t_philo *philo)
{
    if(pthread_mutex_unlock(&philo->utils->forks[philo->r_fork]) != 0)
        return 1;
    if(pthread_mutex_unlock(&philo->utils->forks[philo->l_fork]) != 0)
        return 1;
    return 0;
}

int take_forks(t_philo *philo)
{
    if (pthread_mutex_lock(&philo->utils->forks[philo->r_fork]) != 0)
        return 1;
    printf("%llu %d has taken a fork\n", get_time() - philo->utils->time_start, philo->id);
    if(pthread_mutex_lock(&philo->utils->forks[philo->l_fork]) != 0)
        return 1;
    printf("%llu %d has taken a fork\n", get_time() - philo->utils->time_start, philo->id);
    return 0;
}
int is_sleeping(t_philo *philo)
{
    size_t start_time = get_time();
    if (pthread_mutex_lock(&philo->utils->lock))
        return 1;
    philo->current_state = SLEEP;
    if (pthread_mutex_unlock(&philo->utils->lock))
        return 1;
    printf("%llu %d is sleeping\n", get_time() - philo->utils->time_start, philo->id);
    while(get_time() - start_time < (unsigned long)philo->utils->time_to_sleep)
    {
        // if (philo->utils->death_flag == 1)
        //     return;
        usleep(100);
    }
    return (0);
}
int is_eating(t_philo *philo)
{
    size_t start_time = get_time();
    pthread_mutex_lock(&philo->utils->lock);
    philo->current_state = EAT;
    philo->last_meal = start_time;
    printf("%llu %d is eating\n", get_time() - philo->utils->time_start, philo->id);
    while(get_time() - start_time < (unsigned long)philo->utils->time_to_eat)
        usleep(100);
    pthread_mutex_unlock(&philo->utils->lock);

    return 0;
}

int is_thinking(t_philo *philo)
{
    size_t start_time = get_time();
    pthread_mutex_lock(&philo->utils->lock);
    philo->current_state = THINK;
    philo->last_meal = start_time;
    printf("%llu %d is thinking\n", get_time() - philo->utils->time_start, philo->id);
    pthread_mutex_unlock(&philo->utils->lock);
    return 0;
}

// void *spy_on_philo(void *arg)
// {
//     philo spy
//     printf("test\n");
// }

void *dinning_philo(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        usleep(100);
    while(1)
    {
        if(take_forks(philo) != 0)
        {
            printf("error taking forks\n");
            return NULL;
        }
        if (is_eating(philo))
        {
            printf("error eating\n");
            return NULL;
        }
        if(drop_forks(philo) != 0)
        {
            printf("error dropping forks\n");
            return NULL;
        }
        // philo_eating(philo);
        if(is_sleeping(philo))
        {
            printf("error sleeping\n");
            return NULL;
        }
        if(is_thinking(philo))
        {
            printf("error thinking\n");
            return NULL;
        }
        usleep(10);
    }
    return NULL;
}

int philo_init(t_utils *utils, t_philo *philo, char **av)
{
    // t_philo spy;
    int i = -1;
    philo->utils = utils;
    utils->philo_num = ft_atoi(av[1]);
    utils->time_to_die = ft_atoi(av[2]);
    utils->time_to_eat = ft_atoi(av[3]);
    utils->time_to_sleep = ft_atoi(av[4]);
    utils->death_flag = 0;
    utils->num_of_time_to_eat = ft_atoi(av[5]);
    utils->forks = malloc(sizeof(pthread_mutex_t) * utils->philo_num);
    pthread_mutex_init(&utils->meal, NULL);
    pthread_mutex_init(&utils->printing, NULL);
    pthread_mutex_init(&utils->lock, NULL);
    // spy.utils = utils;
    // spy.id = -1;
    // pthread_init(spy.thread_id, NULL, spy_on_philo, &spy);
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
        pthread_create(&philo[i].thread_id, NULL, dinning_philo, &philo[i]);
        usleep(1);
    }
    
    // if (spy_on_philo(philo))
    //     return 0;
    i = 0;
    while(i < utils->philo_num)
    {
        pthread_join(philo[i].thread_id, NULL);
        i++;
    }
    return 0;
}