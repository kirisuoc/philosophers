/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:56:29 by ecousill          #+#    #+#             */
/*   Updated: 2025/02/06 11:20:29 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor_meals(void *arg)
{
	t_philo_data	*philos;
	int				i;
	int				all_fed;

	philos = (t_philo_data *)arg;
	while (1)
	{
		all_fed = 1;
		i = 0;
		while (i < philos[0].number_of_philosophers)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			if (philos[i].meal_counter < philos[i].times_each_philo_must_eat)
				all_fed = 0;
			pthread_mutex_unlock(&philos[i++].meal_mutex);
		}
		if (all_fed)
		{
			printf("[%ld] Every philosopher has eaten enough.\n", \
				get_elapsed_ms(philos[0].start_time));
			exit(0);
		}
		usleep(10000);
	}
	return (NULL);
}

void	*monitor_philosophers(void *arg)
{
	t_philo_data	*philos;
	int				i;
	long			now;

	philos = (t_philo_data *)arg;
	while (1)
	{
		i = 0;
		while (i < philos[0].number_of_philosophers)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			now = get_elapsed_ms(philos[i].start_time)
			if (philos[i].meal_counter < philos[i].times_each_philo_must_eat)
			{
				if (now - philos[i].last_meal_time > philos[i].time_to_die)
				{
					printf("[%ld] %d died. \n", now, philos[i].id);
					exit(0);
				}
			}
			pthread_mutex_unlock(&philos[i++].meal_mutex);
		}
		usleep(10000);
	}
	return (NULL);
}
