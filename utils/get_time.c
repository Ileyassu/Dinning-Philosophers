#include "../library/philo.h"

size_t get_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}