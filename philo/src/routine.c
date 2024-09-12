/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkarakus <kkarakus@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:25:48 by kkarakus          #+#    #+#             */
/*   Updated: 2024/09/12 15:30:52 by kkarakus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	dead_check_philo(t_philo *philo)
{
	static int	printtable = 1;

	pthread_mutex_lock(philo->data->printing);
	if (philo->control == 0)
	{
		if (get_time() - philo->data->start_t - philo->pres_time >= \
		philo->data->time_to_die)
		{
			if (printtable)
			{
				printf("%lld %d died\n", get_time() - \
					philo->data->start_t, philo->p_id);
				printtable = 0;
			}
			pthread_mutex_lock(philo->data->tf_dies);
			philo->data->tf_die = 1;
			pthread_mutex_unlock(philo->data->tf_dies);
			pthread_mutex_unlock(philo->data->printing);
			return (0);
		}
	}
	pthread_mutex_unlock(philo->data->printing);
	return (1);
}

void	print_situation(t_philo *philo, int64_t time_s, char *str)
{
	check_control(philo);
	pthread_mutex_lock(philo->data->printing);
	if (philo->control != 1)
		printf("%lld %d %s\n", time_s, philo->p_id, str);
	pthread_mutex_unlock(philo->data->printing);
}

static int	ft_sleep(t_philo *philo)
{
	print_situation(philo, get_time() - philo->data->start_t, SLEEP);
	while (dead_check_philo(philo) && philo->control != 1)
	{
		if (get_time() - philo->data->start_t - \
				philo->pres_time == philo->data->time_to_sleep \
					&& philo->control != 1)
			return (1);
		usleep(100);
	}
	return (0);
}

static int	ft_eat(t_philo *philo)
{
	long long	time;

	time = get_time() - philo->data->start_t;
	print_situation(philo, get_time() - philo->data->start_t, EAT);
	while (dead_check_philo(philo) && philo->control != 1 && \
		philo->e_count != philo->data->num_req_eat)
	{
		if (philo->data->time_to_eat == (get_time() - \
			philo->data->start_t - time) \
			&& philo->control != 1)
		{
			philo->pres_time = get_time() - philo->data->start_t;
			philo->e_count++;
			return (1);
		}
		usleep(50);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->control != 1 && philo->e_count != philo->data->num_req_eat)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		check_control(philo);
		print_situation(philo, get_time() - philo->data->start_t, FORKS);
		ft_eat(philo);
		check_control(philo);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		if (philo->control == 1)
			break ;
		ft_sleep(philo);
		check_control(philo);
		if (philo->control == 1)
			break ;
		print_situation(philo, get_time() - philo->data->start_t, THINK);
		check_control(philo);
		if (philo->control == 1)
			break ;
	}
	return (0);
}
