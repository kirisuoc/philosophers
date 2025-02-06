/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:20:58 by ecousill          #+#    #+#             */
/*   Updated: 2025/02/06 14:05:54 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*take_forks(t_philo_data *data, int id)
{
	int				tenedor_izq;
	int				tenedor_der;

	tenedor_izq = id - 1;
	tenedor_der = id % data->number_of_philosophers;
	pthread_mutex_lock(&data->tenedores[tenedor_der]);
	printf("[%ld] %d has taken a fork.\n", \
		get_elapsed_ms(data->start_time), id);
	pthread_mutex_lock(&data->tenedores[tenedor_izq]);
	printf("[%ld] %d has taken a fork.\n", \
		get_elapsed_ms(data->start_time), id);
	return (NULL);
}

void	*to_eat(t_philo_data *data, int id)
{
	printf("[%ld] %d is eating.\n", get_elapsed_ms(data->start_time), id);
	pthread_mutex_lock(&data->meal_mutex);
	data->last_meal_time = get_elapsed_ms(data->start_time);
	data->meal_counter++;
	pthread_mutex_unlock(&data->meal_mutex);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->tenedores[tenedor_der]);
	pthread_mutex_unlock(&data->tenedores[tenedor_izq]);
	return (NULL);
}

void	*to_sleep(t_philo_data *data, int id)
{
	printf("[%ld] %d is sleeping.\n", \
		get_elapsed_ms(data->start_time), id);
	usleep(data->time_to_sleep * 1000);
	return (NULL);
}

void	*to_think(t_philo_data *data, int id)
{
	printf("[%ld] %d is thinking.\n",
		get_elapsed_ms(data->start_time), id);
	return (NULL);
}
