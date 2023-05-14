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
	ssize_t			now;
	struct timeval	time;

	pthread_mutex_lock(&data->time);
	gettimeofday(&time, NULL);
//printf("boot time = %ld\t", data->boot_time);
	now = ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - data->boot_time;
	pthread_mutex_unlock(&data->time);
//printf("%snow = %ld%s\n", GRN, now, CRESET);
	return ((size_t)now);
}

/* Sends the message using mutex according to msg number. */
void	msg_go(t_data *data, int msg, ssize_t time, ssize_t philo)
{
	pthread_mutex_lock(&data->msg);
	if (msg == DIED)
		printf("%ldms %ld died\n", time, philo);
	else if (msg == EAT)
		printf("%ldms %ld is eating\n", time, philo);
	else if (msg == SLEEP)
		printf("%ldms %ld is sleeping\n", time, philo);
	else if (msg == THINK)
		printf("%ldms %ld is thinking\n", time, philo);
	else if (msg == FORK)
		printf("%ldms %ld has taken a fork\n", time, philo);
	pthread_mutex_unlock(&data->msg);
}
