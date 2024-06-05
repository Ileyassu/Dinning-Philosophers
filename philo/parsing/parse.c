/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaiss <ibenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:56:23 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/06/02 18:13:26 by ibenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/philo.h"

int check_last_param(char *num)
{
	int i;

	i = 0;
	while (num[i])
	{
		if ((!ft_isdigit(num[i])))
			return (0);
		i++;
	}
	return (1);
}

int	check_if_arg_num(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (av[i][j])
		{
			if ((!ft_isdigit(av[i][j])) || (ft_atoi(av[1]) > 200)
				|| ft_atoi(av[i]) <= 0)
			{
				printf("Wrong arguments\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	parse_helper(t_utils *utils, char **av)
{
	utils->philo_num = ft_atoi(av[1]);
	utils->time_to_die = ft_atoi(av[2]);
	utils->time_to_eat = ft_atoi(av[3]);
	utils->time_to_sleep = ft_atoi(av[4]);
}

int	parse(t_utils *utils, int ac, char **av)
{
	if (ac - 1 == 5 || ac - 1 == 4)
	{
		if (!check_if_arg_num(av))
			return (0);
		parse_helper(utils, av);
		if (av[5])
		{
			utils->num_of_time_to_eat = ft_atoi(av[5]);
			if (check_last_param(av[5]) == 0 || utils->num_of_time_to_eat < 0)
			{
				printf("Wrong arguments\n");
				return (0);
			}
		}
		if (utils->philo_num < 0 || utils->time_to_die < 0
			|| utils->time_to_eat < 0 || utils->time_to_sleep < 0)
		{
			printf("Wrong arguments\n");
			return (0);
		}
		return (1);
	}
	printf("Add arguments.\n");
	return (0);
}
