#include "philo.h"

/* Boolean checks if philo is dead. And if already eaten the maximum. */
static void	*is_alive(void *pnt)
{	
	t_philo	*philo;
	ssize_t	now;

	philo = (t_philo *)pnt;
	while (1)
	{
		pthread_mutex_lock(&philo->data->alive);
		now = time_now(NULL);
		if (philo->data->max_eat && philo->max_eat == philo->eat_count)
		{
			msg_go(philo->data, EATMAX, now, philo->nbr);
			philo->data->all_alive = 0;
			break ;
		}
		else if (now > philo->will_die)
		{
			msg_go(philo->data, DIED, now, philo->nbr);
			philo->data->all_alive = 0;
			break ;
		}
		usleep(500);
		pthread_mutex_unlock(&philo->data->alive);
	}
	pthread_mutex_unlock(&philo->data->alive);
	return (NULL);
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
	philo->last_eat = time_now(data);
	philo->will_die = philo->last_eat + data->die_time;
	msg_go(data, EAT, philo->last_eat, philo->nbr);
	usleep(data->eat_time * 1000);
//printf("%spassou u sleep%s\n", BLU, CRESET);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&data->philo[prev].mutex);
//printf("%s%ldms philo %ld let go forks%s\n", RED, time_now(data), philo->nbr, CRESET);
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
//printf("%screated philo n %ld%s\n", YEL, data->i + 1, CRESET);
	pos = data->i;
	prev = pos -1;
	if (pos == 0)
		prev = data->total - 1;
	if (pthread_create(&tid, NULL, &is_alive, (void *)&data->philo[pos]))
		philo_dead("Fail to create is_alive threads\n", data);
	pthread_detach(tid);
	while (data->all_alive)
	{
		grab_forks(data, prev, &data->philo[pos]);
		philo_eat(data, prev, &data->philo[pos]);
		philo_sleep(data, &data->philo[pos]);
	}
	//pthread_mutex_unlock(&data->alive);
	//pthread_mutex_unlock(&data->msg);
	return (0);
}
