/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaiss <ibenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:29:26 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/06/02 17:46:49 by ibenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/philo.h"

int	is_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->utils->printing);
	if (philo->utils->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->utils->printing);
		return (1);
	}
	printf("%llu %d is thinking\n", get_time() - philo->utils->time_start,
		philo->id);
	pthread_mutex_unlock(&philo->utils->printing);
	ft_usleep(1);
	return (0);
}

int	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->utils->printing);
	if (philo->utils->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->utils->printing);
		return (1);
	}
	printf("%llu %d is sleeping\n", get_time() - philo->utils->time_start,
		philo->id);
	pthread_mutex_unlock(&philo->utils->printing);
	ft_usleep(philo->utils->time_to_sleep);
	return (0);
}

int	drop_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(&philo->utils->forks[philo->r_fork]) != 0)
		return (1);
	if (pthread_mutex_unlock(&philo->utils->forks[philo->l_fork]) != 0)
		return (1);
	if (is_sleeping(philo))
		return (1);
	if (is_thinking(philo))
		return (1);
	return (0);
}
