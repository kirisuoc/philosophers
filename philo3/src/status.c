/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erikcousillas <erikcousillas@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:55:38 by erikcousill       #+#    #+#             */
/*   Updated: 2025/02/17 09:13:49 by erikcousill      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_philo_data *data)
{
	int		left_fork;
	int		right_fork;

	right_fork = data->id - 1;
	left_fork = data->id % data->number_of_philos;
	if (left_fork > right_fork)
	{
		pthread_mutex_lock(&data->tenedores[right_fork]);
		print_status_change(data->start_time, data->id, 1);
		pthread_mutex_lock(&data->tenedores[left_fork]);
		print_status_change(data->start_time, data->id, 1);
	}
	else
	{
		pthread_mutex_lock(&data->tenedores[left_fork]);
		print_status_change(data->start_time, data->id, 1);
		pthread_mutex_lock(&data->tenedores[right_fork]);
		print_status_change(data->start_time, data->id, 1);
	}
}

void	to_eat(t_philo_data *data)
{
	pthread_mutex_lock(&data->meal_mutex);
	data->last_meal_time = get_elapsed_ms(&data->start_time);
	pthread_mutex_unlock(&data->meal_mutex);
	print_status_change(data->start_time, data->id, 2);
	pthread_mutex_lock(&data->meal_mutex);
	data->meal_counter++;
	pthread_mutex_unlock(&data->meal_mutex);
	usleep(data->time_to_eat * 1000);
}

void	drop_forks(t_philo_data *data)
{
	int				tenedor_izq;
	int				tenedor_der;

	tenedor_der = data->id - 1;
	tenedor_izq = data->id % data->number_of_philos;
	pthread_mutex_unlock(&data->tenedores[tenedor_der]);
	pthread_mutex_unlock(&data->tenedores[tenedor_izq]);
}

void	take_forks_and_eat(t_philo_data *data)
{
	take_forks(data);
	to_eat(data);
	drop_forks(data);
}

void	to_sleep_and_think(t_philo_data *data)
{
	print_status_change(data->start_time, data->id, 3);
	usleep(data->time_to_sleep * 1000);
	print_status_change(data->start_time, data->id, 4);
}
