/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkarakus <kkarakus@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:28:11 by kkarakus          #+#    #+#             */
/*   Updated: 2024/09/12 15:29:04 by kkarakus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include "unistd.h"
# include "pthread.h"
# include <sys/time.h>
# include "stdlib.h"

# define ARGERR "Error: Wrong number of arguments"
# define INARGERR "Error: Invalid arguments"
# define ARRWRONG "You must give numbers."
# define FORKS "has taken forks"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_philo
{
	int				p_id;
	pthread_t		philo;
	int64_t			e_count;
	struct s_data	*data;
	int64_t			pres_time;
	int				control;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_data
{
	t_philo			*id;
	pthread_t		philo;
	int64_t			num_philo;
	int64_t			time_to_die;
	int64_t			time_to_eat;
	int64_t			time_to_sleep;
	int64_t			num_req_eat;
	int				tf_die;
	pthread_mutex_t	*printing;
	pthread_mutex_t	*tf_dies;
	int				err;
	int64_t			start_t;
	pthread_mutex_t	*forks;
}	t_data;

void		check_control(t_philo *philo);
int			dead_check_philo(t_philo *philo);
int			ft_atoi(const char *s);
int			ft_isdigit(char *str);
int64_t		get_time(void);
void		init_struct(t_data *data, int i);
int			null_struct(t_data *data);
void		print_situation(t_philo *philo, int64_t time_s, char *str);
void		*routine(void *arg);

#endif