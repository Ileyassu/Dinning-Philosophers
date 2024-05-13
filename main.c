#include "library/philo.h"

int main(int ac, char **av)
{
    (void)ac;
    t_utils utils;
    parse(&utils, ac, av);
    t_philo philo[ft_atoi(av[1]) + 1]; //creating a tab of philosophers. (should adjust it for the norms)
    philo_init(&utils,philo ,av);
    int i = 1;
    while(philo[i].id != 0)
    {
        printf("main id = %d\n", philo[i].id);
        i++;
    }
}