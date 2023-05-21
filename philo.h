#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define CRESET "\e[0m"

# define DIED	0
# define FORK	1
# define EAT	3
# define SLEEP	2
# define THINK	4
# define EATMAX	5

typedef struct s_philo
{
	ssize_t			nbr;
	int				last_eat;
	int				last_sleep;
	int				will_die;
	ssize_t			eat_count;
	ssize_t			max_eat;
	pthread_mutex_t	mutex;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	time;
	pthread_mutex_t	msg;
	pthread_mutex_t	alive;
	int				all_alive;
	int				boot_time;
	int				now;
	ssize_t			i;
	ssize_t			total;
	int				eat_time;
	int				sleep_time;
	int				die_time;
	ssize_t			max_eat;
}	t_data;

void	*ft_calloc(size_t number, size_t size);
void	msg_go(t_data *data, int msg, ssize_t time, ssize_t philo);
size_t	time_now(t_data *data);

void	data_init(char **argv, int argc, t_data *data);
void	*start_thread(void *data);

void	end_philo(char *str, t_data *data);
void	philo_dead(char *str, t_data *data);

#endif