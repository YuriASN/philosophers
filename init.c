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

	i = -1;
	while (++i < data->total)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		data->philo[i].pos = i;
		data->philo[i].data = data;
		data->philo[i].fork_m = 1;
	}
}

/* Get all arguments passed to program.
	if max_eat == -1 it means that the argument wasn't passed*/
void	data_init(char **argv, int argc, t_data *data)
{
	data->total = ft_atoi(argv[1]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->die_time = ft_atoi(argv[2]);
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	data->philo = 0;
	data->fork = 0;
	data->thread = 0;
	data->philo = ft_calloc(sizeof(*(data->philo)), data->total);
	if (!data->philo)
		end_philo("Failed to malloc data->philo!\n", data);
	data->thread = ft_calloc(sizeof(pthread_t *), data->total);
	if (!data->thread)
		end_philo("Malloc of threads failed!\n", data);
	data->fork = ft_calloc(sizeof(pthread_mutex_t *), data->total);
	if (!data->fork)
		end_philo("Malloc of forks failed!\n", data);
	init_philo(data);
}
