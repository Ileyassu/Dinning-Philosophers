#include "library/philo.h"

int balance = 0;
pthread_mutex_t lock;

int main(int ac, char **av)
{
    (void)ac;
    t_utils utils;
    parse(&utils, ac, av);
    t_philo philo[ft_atoi(av[1])]; //creating a tab of philosophers. (should adjust it for the norms)
    philo_init(&utils,philo ,av);
    utils.philo = philo;
}