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
            if ((!ft_isdigit(av[i][j])) || (ft_atoi(av[1]) > 200))
            {
                printf("Wrong arguments\n");
                exit(1);
            }
            j++;
        }
        i++;
    }
}

int parse(int ac, char **av)
{
    if(ac - 1 != 5)
    {
        printf("Add arguments.\n");
        exit(0);
    }
    check_if_arg_num(av);
    return(1);
}