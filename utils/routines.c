#include "../library/philo.h"

void philo_died (t_philo *philo)
{
    printf("philo %d died\n", philo->id);
}
void philo_eating(t_philo *philo)
{
    size_t start_time = get_time();
    pthread_mutex_lock(&philo->utils->meal);
    while(get_time() - start_time < (unsigned long)philo->utils->time_to_eat)
        usleep(100);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->utils->meal);
}
void philo_sleeping(t_philo *philo)
{
    size_t start_time = get_time();
    while(get_time() - start_time < (unsigned long)philo->utils->time_to_sleep)
    {
        usleep(100);
    }
}