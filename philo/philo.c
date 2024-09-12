/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkarakus <kkarakus@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:40:41 by kkarakus          #+#    #+#             */
/*   Updated: 2024/09/12 15:28:33 by kkarakus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	check_control(t_philo *philo)
{
	pthread_mutex_lock(philo->data->tf_dies);
	philo->control = philo->data->tf_die;
	pthread_mutex_unlock(philo->data->tf_dies);
}

void	*one_philo(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->r_fork);
	print_situation(philo, get_time() - philo->data->start_t, FORKS);
	usleep(philo->data->time_to_die * 1000);
	printf("%lld %d died\n", get_time() - philo->data->start_t, philo->p_id);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

static void	ft_thread(t_data *data)
{
	long long	i;

	i = -1;
	while (++i < data->num_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->num_philo)
	{
		init_struct(data, i);
		data->id[i].r_fork = &data->forks[i];
		data->id[i].l_fork = &data->forks[((i + 1) % data->num_philo)];
	}
	i = -1;
	while (++i < data->num_philo)
	{
		data->err = pthread_create(&data->id[i].philo, NULL,
				routine, &data->id[i]);
		if (data->err)
			return ;
	}
	i = -1;
	while (++i < data->num_philo)
		pthread_join(data->id[i].philo, NULL);
	while (--i > -1)
		pthread_mutex_destroy(&data->forks[i]);
}

static int	argc_checker(t_data *data, char **argv, int argc)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!(ft_isdigit(argv[i])))
			return (free(data->tf_dies), free(data->printing), free(data), 0);
		i++;
	}
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_req_eat = ft_atoi(argv[5]);
	data->id = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->id)
		return (free(data->printing), free(data->tf_dies), free(data), 0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		return (free(data->printing), free(data->tf_dies),
			free(data->id), free(data), 0);
	return (pthread_mutex_init(data->printing, NULL),
		pthread_mutex_init(data->tf_dies, NULL), 1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (printf("%s\n", ARGERR), 0);
	data = malloc(sizeof(t_data));
	if (!data || !null_struct(data) || !argc_checker(data, argv, argc))
		return (0);
	if (data->num_philo > 1)
		ft_thread(data);
	else
	{
		pthread_mutex_init(&data->forks[0], NULL);
		init_struct(data, 0);
		data->id[0].r_fork = &data->forks[0];
		data->err = pthread_create(&data->id[0].philo,
				NULL, one_philo, &data->id[0]);
		if (data->err)
			return (0);
		pthread_join(data->id[0].philo, NULL);
		pthread_mutex_destroy(&data->forks[0]);
	}
	pthread_mutex_destroy(data->printing);
	pthread_mutex_destroy(data->forks);
	return (free(data->printing), free(data->tf_dies), free(data->id),
		free(data->forks), free(data), 1);
}
