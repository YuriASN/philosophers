#include "philo.h"

/* Finishes the programs freeing everything */
void	end_philo(char *str, t_data *data)
{
	if (data)
	{
		if (data->philo)
			free(data->philo);
		if (data->thread)
			free(data->thread);
		free(data);
	}
	if (str)
		printf("%s", str);
	exit (1);
}

/* 	Finishes the threads and free them.
	Afterwords call end_philo to free the data struct and end program. */
void	philo_dead(char *str, t_data *data)
{
	int	i;

	i = -1;
	while (++i < (int)data->total)
		pthread_mutex_destroy(&data->philo[i].mutex);
	pthread_mutex_destroy(&data->msg);
	pthread_mutex_destroy(&data->time);
	pthread_mutex_destroy(&data->alive);
	end_philo(str, data);
}
