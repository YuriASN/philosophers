#include "philo.h"

/* Start the threads and attibutes times for everythig. */
void	*start_thread(void *pt)
{
//	int	last_eat;
//	int	last_sleep;
	t_data	*data;

	data = pt;
	while (1)
	{
		pthread_mutex_lock(&data->fork[data->i]);
		if (data->i == 0)
			pthread_mutex_lock(&data->fork[data->total - 1]);
		else
			pthread_mutex_lock(&data->fork[data->i - 1]);
		printf("%ldms %ld is eating.\n", data->curr_time, data->i +1);
		usleep(data->eat_time);
		pthread_mutex_unlock(&data->fork[data->i]);
		if (data->i == 0)
			pthread_mutex_unlock(&data->fork[data->total - 1]);
		else
			pthread_mutex_unlock(&data->fork[data->i - 1]);
	}
	return (0);
}
