/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaiss <ibenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:29:31 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/06/02 17:54:39 by ibenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/philo.h"

int	check_death_flag_while_taking_forks(t_philo *philo, int first_fork,
		int second_fork)
{
	if (philo->utils->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->utils->forks[first_fork]);
		pthread_mutex_unlock(&philo->utils->forks[second_fork]);
		pthread_mutex_unlock(&philo->utils->printing);
		return (1);
	}
	return (0);
}

void	take_forks_helper(t_philo *philo, int second_fork)
{
	printf("%llu %d has taken a fork\n", get_time() - philo->utils->time_start,
		philo->id);
	pthread_mutex_unlock(&philo->utils->printing);
	pthread_mutex_lock(&philo->utils->forks[second_fork]);
	pthread_mutex_lock(&philo->utils->printing);
}

int	take_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	first_fork = philo->r_fork;
	second_fork = philo->l_fork;
	if (philo->r_fork > philo->l_fork)
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	pthread_mutex_lock(&philo->utils->forks[first_fork]);
	pthread_mutex_lock(&philo->utils->printing);
	if (philo->utils->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->utils->forks[first_fork]);
		pthread_mutex_unlock(&philo->utils->printing);
		return (1);
	}
	take_forks_helper(philo, second_fork);
	if (check_death_flag_while_taking_forks(philo, first_fork, second_fork))
		return (1);
	printf("%llu %d has taken a fork\n", get_time() - philo->utils->time_start,
		philo->id);
	pthread_mutex_unlock(&philo->utils->printing);
	return (0);
}
