
#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>


typedef struct s_philo
{
	ssize_t			last_eat;
	ssize_t			last_sleep;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_t		*thread;
	ssize_t			curr_time;
	ssize_t			i;
	ssize_t			total;
	ssize_t			eat_time;
	ssize_t			sleep_time;
	ssize_t			die_time;
	ssize_t			max_eat;
	pthread_mutex_t	*fork;
}	t_data;



void	data_init(char **argv, int argc, t_data *data);
void	*start_thread(void *data);

void	end_philo(char *str, t_data *data);
void	philo_dead(char *str, t_data *data);

#endif