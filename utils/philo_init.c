#include "../library/philo.h"

int is_thinking(t_philo *philo)
{
    pthread_mutex_lock(&philo->utils->printing);
    if(philo->utils->death_flag == 1)
    {
        pthread_mutex_unlock(&philo->utils->printing);
        return 1;
    }
    printf("%llu %d is thinking\n", get_time() - philo->utils->time_start, philo->id);
    pthread_mutex_unlock(&philo->utils->printing);
    ft_usleep(1);
    return 0;
}

int is_sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->utils->printing);
    if(philo->utils->death_flag == 1)
    {
        pthread_mutex_unlock(&philo->utils->printing);
        return 1;
    }
    printf("%llu %d is sleeping\n", get_time() - philo->utils->time_start, philo->id);
    pthread_mutex_unlock(&philo->utils->printing);
    ft_usleep(philo->utils->time_to_sleep);
    return (0);
}

int drop_forks(t_philo *philo)
{
    if(pthread_mutex_unlock(&philo->utils->forks[philo->r_fork]) != 0)
        return 1;
    if(pthread_mutex_unlock(&philo->utils->forks[philo->l_fork]) != 0)
        return 1;
    if(is_sleeping(philo))
        return 1;
    if(is_thinking(philo))
        return 1;
    return 0;
}

int take_forks(t_philo *philo)
{
    // Ensure the locks are always acquired in a consistent order
    int first_fork = philo->r_fork;
    int second_fork = philo->l_fork;
    
    if (philo->r_fork > philo->l_fork) {
        first_fork = philo->l_fork;
        second_fork = philo->r_fork;
    }
    
    if (pthread_mutex_lock(&philo->utils->forks[first_fork]) != 0)
        return 1;
    pthread_mutex_lock(&philo->utils->printing);
    if(philo->utils->death_flag == 1)
    {
        pthread_mutex_unlock(&philo->utils->forks[first_fork]);
        pthread_mutex_unlock(&philo->utils->printing);
        return 1;
    }
    printf("%llu %d has taken a fork\n", get_time() - philo->utils->time_start, philo->id);
    pthread_mutex_unlock(&philo->utils->printing);

    if(pthread_mutex_lock(&philo->utils->forks[second_fork]) != 0)
    {
        pthread_mutex_unlock(&philo->utils->forks[first_fork]);
        return 1;
    }
    pthread_mutex_lock(&philo->utils->printing);
    if(philo->utils->death_flag == 1)
    {
        pthread_mutex_unlock(&philo->utils->forks[first_fork]);
        pthread_mutex_unlock(&philo->utils->forks[second_fork]);
        pthread_mutex_unlock(&philo->utils->printing);
        return 1;
    }
    printf("%llu %d has taken a fork\n", get_time() - philo->utils->time_start, philo->id);
    pthread_mutex_unlock(&philo->utils->printing);

    return 0;
}

int is_eating(t_philo *philo)
{
    size_t start_time;

    if(take_forks(philo))
        return 1;

    pthread_mutex_lock(&philo->utils->printing);
    if(philo->utils->death_flag == 1)
    {
        pthread_mutex_unlock(&philo->utils->printing);
        return 1;
    }
    start_time = get_time();
    printf("%llu %d is eating\n", get_time() - philo->utils->time_start, philo->id);
    pthread_mutex_unlock(&philo->utils->printing);
    pthread_mutex_lock(&philo->mtx);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->mtx);
    ft_usleep(philo->utils->time_to_eat);
    if(drop_forks(philo))
        return 1;
    return 0;
}
void *supervisor(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    while(1)
    {
        pthread_mutex_lock(&philo->utils->printing);
        if(philo->utils->death_flag == 1)
        {
            pthread_mutex_unlock(&philo->utils->printing);
            return NULL;
        }
        pthread_mutex_unlock(&philo->utils->printing);
        pthread_mutex_lock(&philo->mtx);
        if(get_time() - philo->last_meal >= (unsigned long)philo->utils->time_to_die)
        {
            pthread_mutex_unlock(&philo->mtx);
            pthread_mutex_lock(&philo->utils->printing);
            if(philo->utils->death_flag == 1)
            {
                pthread_mutex_unlock(&philo->utils->printing);
                return NULL;
            }
            philo->utils->death_flag = 1;
            printf("%llu %d died\n", get_time() - philo->utils->time_start, philo->id);
            pthread_mutex_unlock(&philo->utils->printing);
            exit(0);
        }
        pthread_mutex_unlock(&philo->mtx);
        ft_usleep(10);
    }
    return NULL;
}
void *dinning_philo(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    pthread_t supervisor_thread_id;

    if (philo->id % 2 == 0)
        usleep(100);

    if (pthread_create(&supervisor_thread_id, NULL, &supervisor, (void *)philo))
        return ((void *)1);

    while(1)
    {
        if (is_eating(philo))
        {
            break;
        }
        usleep(10);
    }

    // Join the supervisor thread when done
    // pthread_join(supervisor_thread_id, NULL);
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
    pthread_mutex_init(&utils->printing, NULL);
    while(++i < utils->philo_num)
    {
        philo[i].eat = utils->num_of_time_to_eat;
        philo[i].utils = utils;
        philo[i].id = i + 1;
        philo[i].r_fork = i;
        philo[i].l_fork = (i + 1) % utils->philo_num;
        pthread_mutex_init(&utils->forks[i], NULL);
        pthread_mutex_init(&philo[i].mtx, NULL);
    }
    i = -1;
    utils->time_start = get_time();
    while (++i < utils->philo_num)
    {
        philo[i].last_meal = get_time();
        pthread_create(&philo[i].thread_id, NULL, dinning_philo, &philo[i]);
        usleep(1);
    }
    i = -1;
    while(++i < utils->philo_num)
    {
        pthread_join(philo[i].thread_id, NULL);
    }
    i = -1;
    while(++i < utils->philo_num)
    {
        pthread_mutex_destroy(&utils->forks[i]);
        pthread_mutex_destroy(&philo[i].mtx);
    }
    pthread_mutex_destroy(&utils->printing);
    return 0;
}