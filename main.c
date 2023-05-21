#include "philo.h"

/* The isdigit() function checks whether a string
only contains numeric character (0-9) or not.
Return TRUE or FALSE*/
static int	args_are_digit(char **argv, int argc)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			*data;
	struct timeval	time;

	if ((argc != 5 && argc != 6) || !args_are_digit(argv, argc))
		end_philo("Arguments are invalid!\n", NULL);
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		end_philo("Malloc of data struct failed!\n", NULL);
	data_init(argv, argc, data);
printf("%sData init done, press enter to creat threads...%s\n", RED, CRESET); getchar();
	gettimeofday(&time, NULL);
	data->boot_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	data->i = -1;
	while (++data->i < data->total)
	{
		if (pthread_create(&data->thread[data->i], NULL, &start_thread, (void *)data))
			philo_dead("Wasn't able to create thread.\n", data);
		usleep(200);
	}
	while (--data->i >= 0)
	{
		if (pthread_join(data->thread[data->i], NULL))
			printf("Wasn't able to join thread in main.\n");
		pthread_mutex_destroy(&data->philo[data->i].mutex);
	}
	philo_dead(NULL, data);
printf("%sta fechando no main caralho!%s\n", MAG, CRESET);
	return (0);
}
