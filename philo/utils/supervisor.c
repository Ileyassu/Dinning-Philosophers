/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaiss <ibenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:29:28 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/06/02 17:50:43 by ibenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/philo.h"

int	check_death_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->utils->printing);
	if (philo->utils->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->utils->printing);
		return (1);
	}
	pthread_mutex_unlock(&philo->utils->printing);
	return (0);
}

int	checkers(t_philo *philo)
{
	if (finish_eating_check(philo))
		return (1);
	if (check_death_flag(philo))
		return (1);
	pthread_mutex_lock(&philo->mtx);
	if (philo->eat == 0)
	{
		pthread_mutex_unlock(&philo->mtx);
		return (1);
	}
	return (0);
}

void	supervisor_helper(t_philo *philo)
{
	philo->utils->death_flag = 1;
	printf("%llu %d died\n", get_time() - philo->utils->time_start, philo->id);
	pthread_mutex_unlock(&philo->utils->printing);
}

void	*supervisor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (checkers(philo))
			return (NULL);
		if (get_time()
			- philo->last_meal >= (unsigned long)philo->utils->time_to_die)
		{
			pthread_mutex_unlock(&philo->mtx);
			pthread_mutex_lock(&philo->utils->printing);
			if (philo->utils->death_flag == 1)
			{
				pthread_mutex_unlock(&philo->utils->printing);
				return (NULL);
			}
			supervisor_helper(philo);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mtx);
		ft_usleep(10);
	}
	return (NULL);
}
