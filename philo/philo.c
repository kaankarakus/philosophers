/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkarakus <kkarakus@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:40:41 by kkarakus          #+#    #+#             */
/*   Updated: 2024/09/11 11:39:15 by kkarakus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

static int	arg_checker(int ac, t_data data, char *av)
{
		data.num_philo = ft_atoi(av[1]);
		data.time_to_die = ft_atoi(av[2]);
		data.time_to_eat = ft_atoi(av[3]);
		data.time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			data.num_req_eat = ft_atoi(av[5]);
		else
			data.num_req_eat = -1;
		if (data.num_philo < 1 || data.time_to_die < 1 || data.time_to_eat < 1 || data.time_to_sleep < 1 || data.num_req_eat < 1)
			return(printf("%s", INARGERR), 0);
		return (1);
}

static void	ft_thread(t_data data)
{
	pthread_t	*philo;

	philo = malloc(sizeof(pthread_t) * data.num_philo);
	if (!philo)
		return (printf("Error: Malloc failed\n"), 0);
}

int main(int ac, char *av)
{
	t_data data;
		
	if (ac < 5 || ac > 6)
		return (printf("%s", ARGERR), 0);
	if (data.num_philo > 1)
		ft_thread(data);
	
}
