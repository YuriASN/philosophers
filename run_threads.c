#include "philo.h"

/* Start the threads and attibutes times for everythig. */
void	*start_thread(void *pt)
{
//	int	last_eat;
//	int	last_sleep;
	t_data	*data;

	data = pt;
	printf("Locking philo nº %ld.\n", data->i + 1);
	pthread_mutex_lock(&data->fork[data->i]);
	printf("mutex %ld locked.\n", data->i +1);
	pthread_mutex_unlock(&data->fork[data->i]);
	printf("mutex %ld unlocked.\n", data->i +1);
	return (0);
}
