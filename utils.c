#include "philo.h"

/*The memset() function writes len bytes of value c (converted to an
unsigned char) to the string dest. Undefined behaviour from memset(),
resulting from storage overflow, will occur if len	is greater than	the
length of the dest	buffer. The behaviour is also undefined if dest is an
invalid pointer. */
static void	*ft_memset(void *str, int c, int bytes)
{
	int	index;

	index = 0;
	while (index < bytes)
		((unsigned char *)str)[index++] = c;
	return (str);
}

/*The calloc() function allocates space for number of objects, each size
bytes in length. The result is identical to calling malloc() with an
argument of number * size, with the exception that the allocated memory
is explicitly initialized to zero bytes. */
void	*ft_calloc(size_t number, size_t size)
{
	void	*a;

	if ((number * size) == 0)
		return (0);
	a = malloc(number * size);
	if (!a)
		return (0);
	ft_memset(a, 0, (number * size));
	return (a);
}

/* Returns current time in microseconds. */
size_t	time_now(t_data *data)
{
	int				now;
	static int		boot;
	struct timeval	time;

	if (!boot)
	{
		gettimeofday(&time, NULL);
		boot = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
		data->boot_time = boot;
		return ((size_t)boot);
	}
	if (data)
		pthread_mutex_lock(&data->time);
	gettimeofday(&time, NULL);
	now = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	now -= boot;
	if (data)
		pthread_mutex_unlock(&data->time);
//printf("%snow = %ld%s\n", GRN, now, CRESET);
	return ((size_t)now);
}

/* Sends the message using mutex according to msg number. */
void	msg_go(t_data *data, int msg, ssize_t time, ssize_t philo)
{
	pthread_mutex_lock(&data->msg);
	if (data->all_alive)
	{
		if (msg == DIED)
		{
			printf("%s%ldms %ld died%s\n", GRN, time, philo, CRESET);
			pthread_mutex_unlock(&data->alive);
	//		return ;
		}
		else if (msg == EATMAX)
		{
			printf("%s%ldms %ld eaten %ld times.%s\n", GRN, time, philo, data->philo[philo -1].eat_count, CRESET);
			pthread_mutex_unlock(&data->alive);
	//		return ;
		}
		if (msg == EAT)
			printf("%ldms %ld is %seating%s\n", time, philo, YEL, CRESET);
		else if (msg == SLEEP)
			printf("%ldms %ld is %ssleeping%s\n", time, philo, GRN, CRESET);
		else if (msg == THINK)
			printf("%ldms %ld is %sthinking%s\n", time, philo, BLU, CRESET);
		else if (msg == FORK)
			printf("%ldms %ld has taken a fork\n", time, philo);
	}
	pthread_mutex_unlock(&data->msg);
}
