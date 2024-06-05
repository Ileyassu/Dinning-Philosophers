/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaiss <ibenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:28:10 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/06/02 18:16:36 by ibenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library/philo.h"

int	case_one_philo(t_philo *philo, t_utils *utils)
{
	pthread_mutex_init(&utils->printing, NULL);
	philo->id = 1;
	utils->time_start = 0;
	pthread_mutex_lock(&utils->printing);
	printf("%llu %d has taken a fork\n", utils->time_start, philo->id);
	pthread_mutex_unlock(&utils->printing);
	pthread_mutex_lock(&utils->printing);
	printf("%llu %d died\n", utils->time_to_die - utils->time_start, philo->id);
	pthread_mutex_unlock(&utils->printing);
	pthread_mutex_destroy(&utils->printing);
	return (1);
}

int	main(int ac, char **av)
{
	t_utils	utils;
	t_philo	*philo;

	if (!parse(&utils, ac, av))
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!philo)
		return (1);
	if (utils.philo_num == 1)
	{
		case_one_philo(&philo[0], &utils);
		free(philo);
		return (0);
	}
	if (philosophers(&utils, philo, av) == 1)
		return (1);
	else
		return (0);
}
