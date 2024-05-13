#include "../library/philo.h"

pthread_mutex_t order_mutex = PTHREAD_MUTEX_INITIALIZER;
int current_philo = 0;

void where_is_my_spaghetti(t_philo *philo)
{
    philo->eat--;
    printf("Philo %d is eating === philo->eat = %d\n", philo->id, philo->eat);
    usleep(philo->utils->time_to_eat);
}

void philo_sleep(t_philo *philo)
{
    printf("Philo %d is sleeping\n", philo->id);
    usleep(philo->utils->time_to_sleep);
}

void philo_thinking(t_philo *philo)
{
    printf("philo %d is thinking\n", philo->id);
}

void *Dinning_philo(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    (void)philo;

    int i = 12;
    while(i--)
    {
        philo_thinking(philo);
        if(philo->eat == 0)
        {
            printf("philo->eat = %d\n", philo->eat);
            exit(0);
        }
        pthread_mutex_trylock(&philo->r_fork);
        printf("philo-> id = %d right fork is locked\n", philo->id);
        pthread_mutex_trylock(&philo->l_fork);
        printf("philo-> id = %d left fork is locked\n", philo->id);

        where_is_my_spaghetti(philo);
        philo_sleep(philo);
        pthread_mutex_unlock(&philo->r_fork);
        pthread_mutex_unlock(&philo->l_fork);
    }
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
    printf("philo num = %d\n",utils->philo_num);
    pthread_mutex_init(&philo->lock, NULL);
    while(i < utils->philo_num)
    {
        philo[i].eat = utils->num_of_time_to_eat;
        philo[i].utils = utils;
        philo[i].id = i + 1;
        pthread_mutex_init(&philo[i].r_fork, NULL);
        pthread_create(&philo[i].thread_id, NULL, Dinning_philo, &philo[i]);
        i++;
    }
    i = 0;
    while(i < utils->philo_num)
    {
        philo[i].l_fork = philo[(i + utils->philo_num - 1) % utils->philo_num].r_fork;
        i++;
    }
    philo[i].id = 0;
    i = 0;
    while(i < utils->philo_num)
    {
        pthread_join(philo[i].thread_id, NULL);
        i++;
    }   
}