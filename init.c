#include "philo.h"

/* This function returns the converted integral number as an int value.
If no valid conversion could be performed, it returns zero. */
static int	ft_atoi(const char *str)
{
	long	nbr;
	int		sign;
	int		i;

	i = 0;
	nbr = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' )
			sign = -1;
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr *= 10;
		nbr += str[i] - '0';
		++i;
	}
	if ((nbr > 2147483648 && sign == -1) || (nbr > 2147483647 && sign == 1))
		return (0);
	return ((int)nbr * sign);
}

/* Initializates the values of all philos structs.
	Also start mutex on forks. */
static void	init_philo(t_data *data)
{
	ssize_t	i;

	i = 0;
	while (i < data->total)
	{
		data->philo[i].i = i;
		data->philo[i].fork = 1;
		pthread_mutex_init(&data->philo[i].mutex, NULL);
		data->philo[i].data = data;
		data->philo[i].will_die = data->die_time;
		data->philo[i].max_eat = data->max_eat;
		++i;
	}
}

/* Get all arguments passed to program.
	if max_eat == -1 it means that the argument wasn't passed*/
void	data_init(char **argv, int argc, t_data *data)
{
	data->all_alive = 1;
	data->total = ft_atoi(argv[1]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->die_time = ft_atoi(argv[2]);
	if (!data->total || !data->eat_time || !data->sleep_time || !data->die_time)
		end_philo("Argument is 0 or bigger than int\n", data);
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	data->philo = 0;
	data->thread = 0;
	pthread_mutex_init(&data->time, NULL);
	pthread_mutex_init(&data->msg, NULL);
	pthread_mutex_init(&data->alive, NULL);
	data->philo = ft_calloc(sizeof(*(data->philo)), data->total + 1);
	if (!data->philo)
		end_philo("Failed to malloc data->philo!\n", data);
	data->thread = ft_calloc(sizeof(pthread_t *), data->total);
	if (!data->thread)
		end_philo("Malloc of threads failed!\n", data);
	init_philo(data);
}
