#include "../library/philo.h"

void philo_died (t_philo *philo)
{
    printf("philo %d died\n", philo->id);
}
void philo_eating(t_philo *philo)
{
    size_t start_time = get_time();
    philo->last_meal = start_time;
    while(get_time() - start_time < (unsigned long)philo->utils->time_to_eat)
        usleep(100);
    usleep(2000);
}
void philo_sleeping(t_philo *philo)
{
    size_t start_time = get_time();
    while(get_time() - start_time < (unsigned long)philo->utils->time_to_sleep)
    {
        usleep(100);
    }
}