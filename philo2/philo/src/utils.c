/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:54:48 by ecousill          #+#    #+#             */
/*   Updated: 2025/02/11 12:06:49 by ecousill         ###   ########.fr       */
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

void	print_status_change(struct timeval start_time, int id, int option)
{
	if (option == 1)
		printf("[%ld] %d has taken a fork.\n", get_elapsed_ms(&start_time), id);
	else if (option == 2)
		printf("[%ld] %d is eating.\n", get_elapsed_ms(&start_time), id);
	else if (option == 3)
		printf("[%ld] %d is sleeping.\n", get_elapsed_ms(&start_time), id);
	else if (option == 4)
		printf("[%ld] %d is thinking.\n", get_elapsed_ms(&start_time), id);
	else if (option == 5)
	{
		printf("[%ld] %d died.\n", get_elapsed_ms(&start_time), id);
		exit(0);
	}
}
