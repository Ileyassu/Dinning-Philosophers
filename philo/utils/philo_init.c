/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaiss <ibenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:29:23 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/06/02 17:45:50 by ibenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/philo.h"

void	*dinning_philo(void *arg)
{
	t_philo		*philo;
	pthread_t	supervisor_thread_id;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	if (pthread_create(&supervisor_thread_id, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (1)
	{
		if (is_eating(philo))
			break ;
		usleep(10);
	}
	pthread_join(supervisor_thread_id, NULL);
	return (NULL);
}

void	philo_init_helper(t_philo *philo, t_utils *utils)
{
	int	i;

	i = -1;
	while (++i < utils->philo_num)
	{
		philo[i].eat = utils->num_of_time_to_eat;
		philo[i].utils = utils;
		philo[i].has_finished_eating = 0;
		philo[i].id = i + 1;
		philo[i].r_fork = i;
		philo[i].l_fork = (i + 1) % utils->philo_num;
		pthread_mutex_init(&utils->forks[i], NULL);
		pthread_mutex_init(&philo[i].mtx, NULL);
	}
}

int	philo_init(t_utils *utils, t_philo *philo, char **av)
{
	int	i;

	i = -1;
	philo->utils = utils;
	utils->death_flag = 0;
	if (av[5])
	{
		while (++i < utils->philo_num)
			philo[i].eat = utils->num_of_time_to_eat;
	}
	else
		utils->num_of_time_to_eat = -1;
	utils->forks = malloc(sizeof(pthread_mutex_t) * utils->philo_num);
	if (!utils->forks)
		return (1);
	pthread_mutex_init(&utils->printing, NULL);
	pthread_mutex_init(&utils->finish_eating, NULL);
	philo_init_helper(philo, utils);
	i = -1;
	return (0);
}

int	philosophers(t_utils *utils, t_philo *philo, char **av)
{
	int	i;

	i = -1;
	if (philo_init(utils, philo, av))
		return (1);
	utils->time_start = get_time();
	while (++i < utils->philo_num)
	{
		philo[i].last_meal = get_time();
		pthread_create(&philo[i].thread_id, NULL, dinning_philo, &philo[i]);
		usleep(1);
	}
	i = -1;
	while (++i < utils->philo_num)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < utils->philo_num)
	{
		pthread_mutex_destroy(&utils->forks[i]);
		pthread_mutex_destroy(&philo[i].mtx);
	}
	pthread_mutex_destroy(&utils->printing);
	free(utils->forks);
	free(philo);
	return (0);
}
