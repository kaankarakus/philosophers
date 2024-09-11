/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkarakus <kkarakus@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:40:37 by kkarakus          #+#    #+#             */
/*   Updated: 2024/09/11 11:08:49 by kkarakus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int64_t	ft_atoi(char *av)
{
	int64_t	res;
	int64_t	i;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	if (av[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (av[i])
	{
		res = res * 10 + av[i] - '0';
		i++;
	}
	return (res * sign);
}