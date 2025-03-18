/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erikcousillas <erikcousillas@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:12:00 by erikcousill       #+#    #+#             */
/*   Updated: 2025/02/18 04:37:40 by erikcousill      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor_philosophers(void *arg)
{
	t_philo_data	*philos;
	int				i;
	long			now;

	philos = (t_philo_data *)arg;
	while (1)
	{
		i = 0;
		while (i < philos[0].number_of_philos)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			now = get_elapsed_ms(&philos[i].start_time);
			//printf("now: %ld\n", now);
			//printf("last_meal_time: %ld\n", philos[i].last_meal_time);
			if (philos[i].meal_counter < philos[i].times_each_philo_must_eat \
				|| philos[i].times_each_philo_must_eat == -1)
				if (now - philos[i].last_meal_time > philos[i].time_to_die)
				{
					print_status_change(philos[i].start_time, philos[i].id, 5);
					pthread_mutex_unlock(&philos[i].meal_mutex);
					return (NULL);
				}
			pthread_mutex_unlock(&philos[i].meal_mutex);
			i++;
		}
		usleep(10000);
	}
}
