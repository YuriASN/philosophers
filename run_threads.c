#include "philo.h"

/* Checks if philo is dead. And if already eaten the maximum. */
static void	*is_alive(void *pnt)
{
	t_philo	*philo;
	t_data	*data;
	ssize_t	now;

	philo = (t_philo *)pnt;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&data->alive);
		if (!data->all_alive)
			break ;
		now = time_now(data);
		if (data->max_eat
			&& data->max_eat * data->total == data->all_eaten)
			msg_go(data, EATMAX, now, philo->i + 1);
		pthread_mutex_lock(&philo->mutex);
		if (now > philo->will_die && philo->fork != 2)
			msg_go(data, DIED, now, philo->i + 1);
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&data->alive);
		usleep(100);
	}
	pthread_mutex_unlock(&data->alive);
	return (NULL);
}

static void	philo_sleep(t_data *data, t_philo *philo)
{
	msg_go(data, SLEEP, time_now(data), philo->i + 1);
	usleep(data->sleep_time * 1000);
	msg_go(data, THINK, time_now(data), philo->i + 1);
}

/* Lock mutex of both philos. */
static void	grab_forks(t_data *data, size_t prev, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	pthread_mutex_lock(&data->philo[prev].mutex);
	if (philo->i % 2 && philo->fork == 1 && data->philo[prev].fork == 1)
	{
		msg_go(data, FORK, time_now(data), philo->i + 1);
		msg_go(data, FORK, time_now(data), philo->i + 1);
		philo->fork++;
		data->philo[prev].fork--;
	}
	else if (philo->fork == 1 && data->philo[prev].fork == 1)
	{
		msg_go(data, FORK, time_now(data), philo->i + 1);
		msg_go(data, FORK, time_now(data), philo->i + 1);
		data->philo[prev].fork--;
		philo->fork++;
	}
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&data->philo[prev].mutex);
}

/* Eat the food and unlock philo's mutex.*/
static void	philo_eat(t_data *data, size_t prev, t_philo *philo)
{
	philo->last_eat = time_now(data);
	pthread_mutex_lock(&data->alive);
	philo->will_die = philo->last_eat + data->die_time;
	philo->eat_count++;
	data->all_eaten++;
	pthread_mutex_unlock(&data->alive);
	msg_go(data, EAT, philo->last_eat, philo->i + 1);
	usleep(data->eat_time * 1000);
	pthread_mutex_lock(&philo->mutex);
	pthread_mutex_lock(&data->philo[prev].mutex);
	data->philo[prev].fork++;
	philo->fork--;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&data->philo[prev].mutex);
	philo_sleep(philo->data, philo);
}

/* Start the threads and attibutes times for everythig. */
void	*start_thread(void *pt)
{
	ssize_t		prev;
	t_philo		*philo;
	pthread_t	tid;

	philo = pt;
	prev = philo->i -1;
	if (prev == -1)
		prev = philo->data->total - 1;
	if (pthread_create(&tid, NULL, &is_alive, (void *)philo))
		philo_dead("Fail to create is_alive threads\n", philo->data);
	while (1)
	{
		grab_forks(philo->data, prev, philo);
		if (philo->fork == 2)
			philo_eat(philo->data, prev, philo);
		pthread_mutex_lock(&philo->data->alive);
		if (!philo->data->all_alive)
			break ;
		pthread_mutex_unlock(&philo->data->alive);
	}
	pthread_mutex_unlock(&philo->data->alive);
	if (pthread_join(tid, NULL))
		printf("Wasn't able to join is_alive in philo %ld.\n", philo->i);
	return (0);
}
