#include "library/philo.h"

int main(int ac, char **av)
{
    (void)ac;
    t_utils utils;
    if(!parse(&utils, ac, av))
        return (1);
    t_philo *philo = malloc(sizeof(t_philo) * ft_atoi(av[1])); //creating a tab of philosophers. (should adjust it for the norms)
    if (philo_init(&utils,philo ,av) == 1)
    {
        return (1);
    }
}