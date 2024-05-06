#include "library/philo.h"

int balance = 0;
pthread_mutex_t lock;

int main(int ac, char **av)
{
    (void)ac;
    t_utils utils;
    parse(&utils, ac, av);
    t_philo philo[ft_atoi(av[1])];
    philo_init(&utils,philo ,av);
}