#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include "unistd.h"
# include "pthread.h"
# include <sys/time.h>

# define ARGERR "Error: Wrong number of arguments\n"
# define INARGERR "Error: Invalid arguments\n"
# define FORKS "has taken forks\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"

typedef struct s_philo
{
	int				p_id;
	pthread_t		philo;
	long long		e_count;
	struct s_data	*data;
	long long		pres_time;
	int				control;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_data
{
	t_philo			*id;
	pthread_t		phio;
	int64_t			num_philo;
	int64_t			time_to_die;
	int64_t			time_to_eat;
	int64_t			time_to_sleep;
	int64_t			num_req_eat;
	int				tf_die;
	pthread_mutex_t	*printing;
	pthread_mutex_t	*tf_dies;
	int				err;
	long long		start_t;
	pthread_mutex_t	*forks;
}	t_data;

int64_t	ft_atoi(char *av);

#endif