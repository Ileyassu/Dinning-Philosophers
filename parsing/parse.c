#include "../library/philo.h"

void check_if_arg_num(char **av)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while(i < 5)
    {
        j = 0;
        while(av[i][j])
        {
            if ((!ft_isdigit(av[i][j])) || (ft_atoi(av[1]) > 200) || ft_atoi(av[i]) <= 0)
            {
                printf("Wrong arguments\n");
                exit(1);
            }
            j++;
        }
        i++;
    }
}

int parse(t_utils *utils, int ac, char **av)
{
    if(ac - 1 != 5)
    {
        printf("Add arguments.\n");
        exit(0);
    }
    check_if_arg_num(av);
    utils->philo_num = ft_atoi(av[1]);
    utils->time_to_die = ft_atoi(av[2]);
    utils->time_to_eat = ft_atoi(av[3]);
    utils->time_to_sleep = ft_atoi(av[4]);
    utils->num_of_time_to_eat = ft_atoi(av[5]);
    return(1);
}