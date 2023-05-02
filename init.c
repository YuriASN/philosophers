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

/* Get all arguments passed to program.
	if max_eat == -1 it means that the argument wasn't passed*/
void	data_init(char **argv, int argc, t_data *data)
{
	int	i;

	data->curr_time = 0;
	data->total = ft_atoi(argv[1]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->die_time = ft_atoi(argv[2]);
	data->max_eat = -1;
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	data->philo = 0;
	data->fork = 0;
	data->thread = 0;
	data->philo = malloc(sizeof(t_philo) * data->total);
	if (!data->philo)
		end_philo("Failed to malloc data->philo!\n", data);
	data->thread = malloc(sizeof(pthread_t *) * data->total);
	if (!data->thread)
		end_philo("Malloc of threads failed!\n", data);
	data->fork = malloc(sizeof(pthread_mutex_t *) * data->total);
	if (!data->fork)
		end_philo("Malloc of forks failed!\n", data);
	i = -1;
	while (++i < data->total)
		pthread_mutex_init(&data->fork[i], NULL);
	data->i = -1;
}