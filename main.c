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
	struct timeval	current_time;

	if (argc != 5 && argc != 6)
		end_philo("Number of arguments is invalid!\n", NULL);
	if (!args_are_digit(argv, argc))
		end_philo("A argument is invalid!\n", NULL);
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		end_philo("Malloc of data struct failed!\n", NULL);
	data_init(argv, argc, data);

	while (1)
	{
		gettimeofday(&current_time, NULL);
		data->curr_time = current_time.tv_usec;
		data->i = -1;
		while (++data->i < data->total)
		{
			if (pthread_create(&data->thread[data->i], NULL, &start_thread, (void *)data))
				philo_dead("Wasn't able to create thread.\n", data);
		}
	}
	return (0);
}
