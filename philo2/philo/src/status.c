/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:20:58 by ecousill          #+#    #+#             */
/*   Updated: 2025/02/11 11:43:14 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_philo_data *data, int id)
{
	int				tenedor_izq;
	int				tenedor_der;

	tenedor_der = id - 1;
	tenedor_izq = id % data->number_of_philos;
	if (tenedor_izq > tenedor_der)
	{
		pthread_mutex_lock(&data->tenedores[tenedor_der]);
		print_status_change(data->start_time, id, 1);
		pthread_mutex_lock(&data->tenedores[tenedor_izq]);
		print_status_change(data->start_time, id, 1);
	}
	else
	{
		pthread_mutex_lock(&data->tenedores[tenedor_izq]);
		print_status_change(data->start_time, id, 1);
		pthread_mutex_lock(&data->tenedores[tenedor_der]);
		print_status_change(data->start_time, id, 1);
	}
}

void	to_eat(t_philo_data *data, int id)
{
	pthread_mutex_lock(&data->meal_mutex);
	data->last_meal_time = get_elapsed_ms(&data->start_time);
	pthread_mutex_unlock(&data->meal_mutex);
	print_status_change(data->start_time, id, 2);
	pthread_mutex_lock(&data->meal_mutex);
	data->meal_counter++;
	pthread_mutex_unlock(&data->meal_mutex);
	usleep(data->time_to_eat * 1000);
}

void	drop_forks(t_philo_data *data, int id)
{
	int				tenedor_izq;
	int				tenedor_der;

	tenedor_der = id - 1;
	tenedor_izq = id % data->number_of_philos;
	pthread_mutex_unlock(&data->tenedores[tenedor_der]);
	pthread_mutex_unlock(&data->tenedores[tenedor_izq]);
}

void	*take_forks_and_eat(t_philo_data *data, int id)
{
	take_forks(data, id);
	to_eat(data, id);
	drop_forks(data, id);
	return (NULL);
}

void	*to_sleep_and_think(t_philo_data *data, int id)
{
	print_status_change(data->start_time, id, 3);
	usleep(data->time_to_sleep * 1000);
	print_status_change(data->start_time, id, 4);
	return (NULL);
}
