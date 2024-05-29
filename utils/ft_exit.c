#include "../library/philo.h"

// void	clear_data(t_utils	*utils)
// {

// }
// int join_threads(t_utils *utils)
// {
//     int	i;

//     i = -1;
//     while (++i < utils->philo_num)
//     {
//         printf("ici\n");
//         if (pthread_join(utils->philo[i].thread_id, NULL))
//             return (1);
        
//     }
//     return (0);
// }
int threads_detach(t_utils *utils)
{
    int	i;

    i = -1;
    while (++i < utils->philo_num)
    {
        if (pthread_detach(utils->philo[i].thread_id))
            return (1);
    }
    return (0);
}

void	ft_exit(t_utils *utils)
{
	int	i;
	i = -1;
    // if(join_threads(utils))
    // {
    //     printf("error joining threads\n");
    //     return ;
    // }
    if(threads_detach(utils))
    {
        printf("error detaching threads\n");
        return ;
    }
	while (++i < utils->philo_num)
	{
		pthread_mutex_destroy(&utils->forks[i]);
		pthread_mutex_destroy(&utils->lock);
	}
    free(utils->forks);
	pthread_mutex_destroy(&utils->lock);
	// clear_data(utils);
}