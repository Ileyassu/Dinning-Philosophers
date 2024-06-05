/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaiss <ibenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:29:21 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/06/02 17:40:58 by ibenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/philo.h"

int	finish_eating_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->utils->finish_eating);
	if (philo->utils->num_of_time_to_eat == 0)
	{
		pthread_mutex_unlock(&philo->utils->finish_eating);
		return (1);
	}
	pthread_mutex_unlock(&philo->utils->finish_eating);
	return (0);
}

int	eating_checkers(t_philo *philo)
{
	if (philo->has_finished_eating == 1 || philo->eat == 0)
		return (1);
	if (take_forks(philo))
		return (1);
	pthread_mutex_lock(&philo->utils->printing);
	if (philo->utils->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->utils->printing);
		return (1);
	}
	return (0);
}

void	philo_finished_eating(t_philo *philo)
{
	philo->has_finished_eating = 1;
	pthread_mutex_lock(&philo->utils->finish_eating);
	philo->utils->num_of_time_to_eat--;
	pthread_mutex_unlock(&philo->utils->finish_eating);
	pthread_mutex_unlock(&philo->mtx);
	pthread_mutex_unlock(&philo->utils->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->utils->forks[philo->l_fork]);
}

int	is_eating(t_philo *philo)
{
	if (eating_checkers(philo))
		return (1);
	printf("%llu %d is eating\n", get_time() - philo->utils->time_start,
		philo->id);
	pthread_mutex_unlock(&philo->utils->printing);
	pthread_mutex_lock(&philo->mtx);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mtx);
	ft_usleep(philo->utils->time_to_eat);
	pthread_mutex_lock(&philo->mtx);
	if (philo->eat > 0)
		philo->eat--;
	if (philo->eat == 0)
	{
		philo_finished_eating(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->mtx);
	if (drop_forks(philo))
		return (1);
	return (0);
}
