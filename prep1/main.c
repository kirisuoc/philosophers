/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:17:54 by ecousill          #+#    #+#             */
/*   Updated: 2025/01/29 16:32:31 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_comidas(void *arg)
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

void	*monitor_filosofos(void *arg)
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
			now = get_elapsed_ms(philos[i].start_time);
			if (philos[i].meal_counter < philos[i].times_each_philo_must_eat)
			{
				if (now - philos[i].last_meal_time > philos[i].time_to_die)
				{
					printf("[%ld] %d died.\n", now, philos[i].id);
					exit(0);
				}
			}
			pthread_mutex_unlock(&philos[i++].meal_mutex);
		}
		usleep(10000);
	}
	return (NULL);
}

void	*filosofo(void *arg)
{
	t_philo_data	*data;
	int				id;
	int				tenedor_izq;
	int				tenedor_der;

	data = (t_philo_data *)arg;
	id = data->id;
	tenedor_izq = id - 1;
	tenedor_der = id % data->number_of_philosophers;
	while (1)
	{
		if (data->id == data->number_of_philosophers - 1)
		{
			pthread_mutex_lock(&data->tenedores[tenedor_der]);
			printf("[%ld] %d has taken a fork.\n", \
				get_elapsed_ms(data->start_time), id);
			pthread_mutex_lock(&data->tenedores[tenedor_izq]);
			printf("[%ld] %d has taken a fork.\n", \
				get_elapsed_ms(data->start_time), id);
		}
		else
		{
			pthread_mutex_lock(&data->tenedores[tenedor_izq]);
			printf("[%ld] %d has taken a fork.\n", \
				get_elapsed_ms(data->start_time), id);
			pthread_mutex_lock(&data->tenedores[tenedor_der]);
			printf("[%ld] %d has taken a fork.\n", \
				get_elapsed_ms(data->start_time), id);
		}
		printf("[%ld] %d is eating.\n", get_elapsed_ms(data->start_time), id);
		pthread_mutex_lock(&data->meal_mutex);
		data->last_meal_time = get_elapsed_ms(data->start_time);
		data->meal_counter++;
		pthread_mutex_unlock(&data->meal_mutex);
		printf("[%ld] %d has eaten %d times. -- Quitar\n", \
			get_elapsed_ms(data->start_time), id, data->meal_counter);
		usleep(data->time_to_eat * 1000);
		pthread_mutex_unlock(&data->tenedores[tenedor_der]);
		pthread_mutex_unlock(&data->tenedores[tenedor_izq]);
		printf("[%ld] %d is sleeping.\n", \
			get_elapsed_ms(data->start_time), id);
		usleep(data->time_to_sleep * 1000);
		printf("[%ld] %d is thinking.\n",
			get_elapsed_ms(data->start_time), id);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	struct timeval	start_time;
	int				times_each_philo_must_eat;
	pthread_t		filosofos[number_of_philosophers];
	pthread_mutex_t	tenedores[number_of_philosophers];
	t_philo_data	philo_data[number_of_philosophers];
	int				i;

	gettimeofday(&start_time, NULL);
	if (ac < 5 || ac > 6)
	{
		printf("Uso: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [times_each_philo_must_eat]\n", av[0]);
		return (1);
	}
	times_each_philo_must_eat = -1;
	if (ac == 6)
		times_each_philo_must_eat = ft_atoi(av[5]);
	if (number_of_philosophers <= 0 || time_to_die <= 0 || time_to_eat <= 0 || time_to_sleep <= 0 \
		|| (ac == 6 && times_each_philo_must_eat <= 0))
	{
		printf("Error. Todos los argumentos deben ser positivos.\n");
		return (1);
	}

	i = 0;
	// Inicializar los mutex (tenedores)
	while (i < number_of_philosophers)
		pthread_mutex_init(&tenedores[i++], NULL);

	i = 0;
	// Crear los hilos (filósofos)
	while (i < number_of_philosophers)
	{
		philo_data[i].id = i + 1;
		philo_data[i].number_of_philosophers = ft_atoi(av[1]);
		philo_data[i].time_to_die = ft_atoi(av[2]);
		philo_data[i].time_to_eat = ft_atoi(av[3]);
		philo_data[i].time_to_sleep = ft_atoi(av[4]);
		philo_data[i].tenedores = tenedores;
		philo_data[i].times_each_philo_must_eat = times_each_philo_must_eat;
		philo_data[i].start_time = start_time;	// Momento del inicio del programa
		philo_data[i].meal_counter = 0;
		philo_data[i].last_meal_time = get_time_in_ms();
		pthread_mutex_init(&philo_data[i].meal_mutex, NULL);

		pthread_create(&filosofos[i], NULL, filosofo, &philo_data[i]);
		i++;
	}

	// Crear hilos de monitorización
	pthread_t	monitor_filosofos_thread;
	pthread_create(&monitor_filosofos_thread, NULL, monitor_filosofos, philo_data);
	if (times_each_philo_must_eat > 0)
	{
		pthread_t	monitor_comidas_thread;
		pthread_create(&monitor_comidas_thread, NULL, monitor_comidas, philo_data);
	}

	i = 0;
	// Esperar a que los hilos terminen (nunca pasa, ya que es un bucle infinito (?))
	while (i < number_of_philosophers)
		pthread_join(filosofos[i++], NULL);

	i = 0;
	// Destruir los mutex (nunca se llega aquí (?))
	while (i < number_of_philosophers)
		pthread_mutex_destroy(&tenedores[i++]);

	return (0);
}
