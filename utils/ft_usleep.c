#include "../library/philo.h"

int	ft_usleep(size_t time)
{
	size_t	start;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return(0);
}