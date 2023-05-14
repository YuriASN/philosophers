#include "philo.h"

/* Boolean checks if philo is dead. And if already eaten the maximum. */
static void	*is_alive(void *pnt)
{	
	t_data	*data;
	ssize_t	now;

	data = (t_data *)pnt;
	while (1)
	{
		now = time_now(data);
		if (data->max_eat && data->max_eat == data->philo[data->i].eat_count)
			philo_dead("Reached maximum eat times.\n", data);
		if (now > data->philo[data->i].will_die)
		{
			data->all_alive = 0;
			msg_go(data, DIED, now, data->i + 1);
printf("philo %ld, now = %ld, will_die =%ld\n", data->i + 1, now, data->philo[data->i].will_die);
			philo_dead(NULL, data);
		}
		usleep(990);
	}
	return(NULL);
}

/* Lock mutex of both philos. */
static void	grab_forks(t_data *data, size_t prev, t_philo *philo)
{
	pthread_mutex_lock(&data->philo[prev].mutex);
	msg_go(data, FORK, time_now(data), philo->nbr);
	pthread_mutex_lock(&philo->mutex);
	msg_go(data, FORK, time_now(data), philo->nbr);
}

/* Eat the food and unlock philo's mutex.*/
static void	philo_eat(t_data *data, size_t prev, t_philo *philo)
{
//	philo->fork = 0;
//	data->philo[prev].fork = 0;
	philo->last_eat = time_now(data);
	philo->will_die = philo->last_eat + data->die_time;
	msg_go(data, EAT, philo->last_eat, philo->nbr);
	usleep(data->eat_time * 1000);
printf("%spassou u sleep%s\n", BLU, CRESET);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&data->philo[prev].mutex);
printf("%ldms philo %ld let go forks\n", time_now(data), philo->nbr);
//	philo->fork = 1;
//	data->philo[prev].fork = 1;
}

static void	philo_sleep(t_data *data, t_philo *philo)
{
	msg_go(data, SLEEP, time_now(data), philo->nbr);
	usleep(data->sleep_time * 1000);
	msg_go(data, THINK, time_now(data), philo->nbr);
}

/* Start the threads and attibutes times for everythig. */
void	*start_thread(void *pt)
{
	size_t		pos;
	ssize_t		prev;
	t_data		*data;
	pthread_t	tid;

	data = pt;
printf("%screated philo n %ld%s\n", YEL, data->i + 1, CRESET);
	pos = data->i;
	prev = pos -1;
	if (pos == 0)
		prev = data->total - 1;
	usleep(100);
	if(pthread_create(&tid, NULL, &is_alive, (void *)data))
		philo_dead(NULL, data);
	pthread_detach(tid);
	while (data->all_alive)
	{
		grab_forks(data, prev, &data->philo[pos]);
		philo_eat(data, prev, &data->philo[pos]);
		philo_sleep(data, &data->philo[pos]);
	}
printf("got out of while\n");
	return (0);
}
