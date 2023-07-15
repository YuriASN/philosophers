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

/* Kill philosopher after time to die if there's only one of them */
static void	only_one(t_data *data)
{
	time_now(data);
	usleep(data->die_time * 1000);
	printf("%s%ldms 1 died%s\n", GRN, time_now(data), CRESET);
	end_philo(NULL, data);
}

static t_data	*start_data(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		end_philo("Malloc of data struct failed!\n", NULL);
	data_init(argv, argc, data);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	if ((argc != 5 && argc != 6) || !args_are_digit(argv, argc))
		end_philo("Arguments are invalid!\n", NULL);
	data = start_data(argc, argv);
	i = -1;
	if (data->total == 1)
		only_one(data);
	while (++i < data->total)
	{
		if (pthread_create(&data->thread[i], NULL,
				&start_thread, (void *)&data->philo[i]))
			philo_dead("Wasn't able to create thread.\n", data);
		usleep(200);
	}
	while (--i >= 0)
	{
		if (pthread_join(data->thread[i], NULL))
			printf("Wasn't able to join thread in main.\n");
	}
	philo_dead(NULL, data);
	return (0);
}
