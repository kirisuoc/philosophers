/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erikcousillas <erikcousillas@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:35:46 by erikcousill       #+#    #+#             */
/*   Updated: 2025/02/17 08:46:59 by erikcousill      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	create_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philos)
	{
		sim->philo_data[i].id = i + 1;
		sim->philo_data[i].meal_counter = 0;
		sim->philo_data[i].last_meal_time = timeval_to_ms(sim->start_time);
		sim->philo_data[i].start_time = sim->start_time;
		sim->philo_data[i].number_of_philos = sim->number_of_philos;
		sim->philo_data[i].time_to_die = ft_atoi(sim->av[2]);
		sim->philo_data[i].time_to_eat = ft_atoi(sim->av[3]);
		sim->philo_data[i].time_to_sleep = ft_atoi(sim->av[4]);
		sim->philo_data[i].tenedores = sim->tenedores;
		if (sim->ac == 6)
			sim->philo_data[i].times_each_philo_must_eat = ft_atoi(sim->av[5]);
		else
			sim->philo_data[i].times_each_philo_must_eat = -1;
		pthread_mutex_init(&sim->philo_data[i].meal_mutex, NULL);
		pthread_create(&sim->philosophers[i], NULL, philosopher, \
			&sim->philo_data[i]);
		i++;
	}
}
