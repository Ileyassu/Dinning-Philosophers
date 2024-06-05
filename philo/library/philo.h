/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaiss <ibenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:29:51 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/06/02 17:33:55 by ibenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_utils
{
	long long		time_start;
	int				death_flag;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_time_to_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printing;
	pthread_mutex_t	finish_eating;
}					t_utils;

typedef struct s_philo
{
	int				r_fork;
	int				l_fork;
	int				eat;
	int				i;
	unsigned long	last_meal;
	int				has_finished_eating;
	pthread_mutex_t	mtx;
	t_utils			*utils;
	pthread_t		thread_id;
	int				id;
}					t_philo;

int					philosophers(t_utils *utils, t_philo *philo, char **av);
int					ft_isdigit(int arg);
int					ft_usleep(size_t time);
int					ft_atoi(const char *pt);
int					philo_init(t_utils *utils, t_philo *philo, char **av);
int					parse(t_utils *utils, int ac, char **av);
size_t				get_time(void);
void				philo_init_helper(t_philo *philo, t_utils *utils);
int					is_thinking(t_philo *philo);
int					is_sleeping(t_philo *philo);
int					drop_forks(t_philo *philo);
int					check_death_flag_while_taking_forks(t_philo *philo,
						int first_fork, int second_fork);
void				take_forks_helper(t_philo *philo, int second_fork);
int					take_forks(t_philo *philo);
int					eating_checkers(t_philo *philo);
void				philo_finished_eating(t_philo *philo);
int					is_eating(t_philo *philo);
int					finish_eating_check(t_philo *philo);
int					check_death_flag(t_philo *philo);
int					checkers(t_philo *philo);
void				*supervisor(void *arg);
void				*dinning_philo(void *arg);

#endif
