/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:17:54 by ecousill          #+#    #+#             */
/*   Updated: 2025/01/29 12:17:18 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
ARGS:
	number_of_philosophers -> nº filósofos y nº tenedores
	time_to_die -> tiempo que tiene para comer antes de morir desde inicio programa o última comida
	time_to_eat -> tiempo para comer, tiene los tenedores ocupados
	time_to_sleep -> tiempo que pasa durmiendo
	[number_of_times_each_philosopher_must_eat] -> (opcional) Si se indica, la simulación termina cuando todos coman se nº de veces.
													Si no, cuando uno muera.
*/

#include "philo.h"

void	*monitor_comidas(void *arg)
{
	t_philo_data	*philos = (t_philo_data * )arg;
	int				i;
	int				all_fed;


	while (1)
	{
		all_fed = 1;

		int	j;
		j = 0;
		i = 0;

		while (i < philos[0].number_of_philosophers)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			if (philos[i].meal_counter < philos[i].number_of_times_each_philosopher_must_eat)
				all_fed = 0;	// Si un filósofo no ha comido suficiente
			pthread_mutex_unlock(&philos[i].meal_mutex);
			i++;
		}
		if (all_fed)
		{
			printf("[%ld] Todos los filósofos han comido al menos %d veces. Fin de la simulación.\n", get_elapsed_ms(philos[0].start_time), philos[0].number_of_times_each_philosopher_must_eat);
			exit(0);
		}
		usleep(10000);	// Revisar cada 10ms
	}
	return (NULL);
}

void	*monitor_filosofos(void *arg)
{
	t_philo_data	*philos = (t_philo_data *)arg;
	int				i;
	long			current_time;

	while (1)
	{
		i = 0;

		while (i < philos[0].number_of_philosophers)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			current_time = get_elapsed_ms(philos[i].start_time);

			// Solo verificamos la muerte si el filósofo no ha comido lo suficiente
			if (philos[i].meal_counter < philos[i].number_of_times_each_philosopher_must_eat)
			{
				if (current_time - philos[i].last_meal_time > philos[i].time_to_die)
				{
					printf("[%ld] %d died.\n", current_time, philos[i].id);
					exit(0);
				}
			}
			pthread_mutex_unlock(&philos[i].meal_mutex);
			i++;
		}
		usleep(10000);
	}
	return (NULL);
}

void	*filosofo(void *arg)
{
	t_philo_data *data = (t_philo_data *)arg;				// Convertir el argumento
	int	id = data->id;
	int	tenedor_izq = id - 1;									// Tenedor a la izquierda del filósofo
	int	tenedor_der = id % data->number_of_philosophers;	// Tenedor a la derecha del filósofo

	while (1)
	{
		// Intentar comer
		//printf("[%ld] %d tiene hambre.\n", get_elapsed_ms(data->start_time), id);

		// Tomar los tenedores (bloquear mutex)
		pthread_mutex_lock(&data->tenedores[tenedor_izq]);
		printf("[%ld] %d has taken a fork.\n", get_elapsed_ms(data->start_time), id);

		pthread_mutex_lock(&data->tenedores[tenedor_der]);
		printf("[%ld] %d has taken a fork.\n", get_elapsed_ms(data->start_time), id);


		// Comer
		printf("[%ld] %d is eating.\n", get_elapsed_ms(data->start_time), id);

		// Incrementar el contador de comidas de manera segura
		pthread_mutex_lock(&data->meal_mutex);
		data->last_meal_time = get_elapsed_ms(data->start_time);	// Actualizar última comida
		data->meal_counter++;
		pthread_mutex_unlock(&data->meal_mutex);

		printf("[%ld] %d has eaten %d times.\n", get_elapsed_ms(data->start_time), id, data->meal_counter);
		usleep(data->time_to_eat * 1000);

		// Soltar los tenedores (desbloquear mutex)
		pthread_mutex_unlock(&data->tenedores[tenedor_der]);
		pthread_mutex_unlock(&data->tenedores[tenedor_izq]);

		// Dormir
		printf("[%ld] %d is sleeping.\n", get_elapsed_ms(data->start_time), id);
		usleep(data->time_to_sleep * 1000);

		// Pensar
		printf("[%ld] %d is thinking.\n", get_elapsed_ms(data->start_time), id);
		//usleep(300000);
	}
	return (NULL);
}


int	main(int ac, char **av)
{

	struct	timeval start_time;

	// Obtener el tiempo de inicio
	gettimeofday(&start_time, NULL);

	// Validar número de argumentos
	if (ac < 5 || ac > 6)
	{
		printf("Uso: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", av[0]);
		return (1);
	}
	int	number_of_philosophers = ft_atoi(av[1]);
	int	time_to_die = ft_atoi(av[2]);
	int	time_to_eat = ft_atoi(av[3]);
	int	time_to_sleep = ft_atoi(av[4]);
	int	number_of_times_each_philosopher_must_eat =  -1;

	if (ac == 6)
		number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);

	// Verificar que todos los argumentos son positivos
	if (number_of_philosophers <= 0 || time_to_die <= 0 || time_to_eat <= 0 || time_to_sleep <= 0 \
		|| (ac == 6 && number_of_times_each_philosopher_must_eat <= 0))
	{
		printf("Error. Todos los argumentos deben ser positivos.\n");
		return (1);
	}

	// Mostrar valores recibidos (para depuración)
	printf("Philosophers: %d\n", number_of_philosophers);
	printf("Time to die: %d ms\n", time_to_die);
	printf("Time to eat: %d ms\n", time_to_eat);
	printf("Time to sleep: %d ms\n", time_to_sleep);
	printf("Times each philosopher must eat: %d\n", number_of_times_each_philosopher_must_eat);

	pthread_t	filosofos[number_of_philosophers];
	pthread_mutex_t tenedores[number_of_philosophers];
	t_philo_data	philo_data[number_of_philosophers];

	int	i;

	i = 0;
	// Inicializar los mutex (tenedores)
	while (i < number_of_philosophers)
		pthread_mutex_init(&tenedores[i++], NULL);

	i = 0;
	// Crear los hilos (filósofos)
	while (i < number_of_philosophers)
	{
		philo_data[i].id = i + 1;
		philo_data[i].number_of_philosophers = number_of_philosophers;
		philo_data[i].time_to_eat = time_to_eat;
		philo_data[i].time_to_sleep = time_to_sleep;
		philo_data[i].time_to_die = time_to_die;
		philo_data[i].tenedores = tenedores;
		philo_data[i].number_of_times_each_philosopher_must_eat = number_of_times_each_philosopher_must_eat;
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

	if (number_of_times_each_philosopher_must_eat > 0)
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
