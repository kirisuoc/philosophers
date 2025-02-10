/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erikcousillas <erikcousillas@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:54:48 by ecousill          #+#    #+#             */
/*   Updated: 2025/02/08 16:36:35 by erikcousill      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	number;
	int	sign;

	i = 0;
	number = 0;
	sign = 1;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
		if (nptr[i] == '-' || nptr[i] == '+')
			return (0);
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] - '0');
		i++;
	}
	return (number * sign);
}

long	get_elapsed_ms(struct timeval *start_time)
{
	struct timeval	current_time;
	long			elapsed_ms;

	gettimeofday(&current_time, NULL);
	elapsed_ms = (current_time.tv_sec - start_time->tv_sec) \
		* 1000 + (current_time.tv_usec - start_time->tv_usec) / 1000;
	return (elapsed_ms);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
