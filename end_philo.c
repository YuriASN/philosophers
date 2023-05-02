#include "philo.h"

/* Finishes the programs freeing everything */
void	end_philo(char *str, t_data *data)
{
	int	i;

	i = -1;
	if (data)
	{
		if (data->fork)
			while (++i < data->total)
				pthread_mutex_destroy(&data->fork[i]);
		if (data->philo)
			free(data->philo);
		free(data);
	}
	printf("%s", str);
	exit (1);
}

/* 	Finishes the threads and free them.
	Afterwords call end_philo to free the data struct and end program. */
void	philo_dead(char *str, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->total)
		if (pthread_join(data->thread[data->i], NULL) != 0)
			printf("Thread %ld wasn't able to join.\n", data->i);
	end_philo(str, data);
}
