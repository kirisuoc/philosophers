/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erikcousillas <erikcousillas@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:06:37 by ecousill          #+#    #+#             */
/*   Updated: 2025/02/10 11:54:35 by erikcousill      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philosopher(void *arg)
{
	t_philo_data	*data;

	data = (t_philo_data *)arg;
	while (1)
	{
		take_forks_and_eat(data, data->id);
		//to_eat(data, data->id);
		to_sleep(data, data->id);
		to_think(data, data->id);
	}
	return (NULL);
}

int	check_errors(int ac, char **av)
{
	int	times_each_philo_must_eat;

	times_each_philo_must_eat = -1;
	if (ac < 5 || ac > 6)
	{
		printf("Use: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [times_each_philo_must_eat]\n", av[0]);
		return (1);
	}
	if (ac == 6)
		times_each_philo_must_eat = ft_atoi(av[5]);

	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 \
		|| ft_atoi(av[4]) <= 0 || (ac == 6 && times_each_philo_must_eat <= 0))
	{
		printf("Error. All arguments given must be greater than 0.\n");
		return (1);
	}
	return (0);
}

void	create_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		sim->philo_data[i].id = i + 1;
		sim->philo_data[i].number_of_philosophers = sim->number_of_philosophers;
		sim->philo_data[i].time_to_die = ft_atoi(sim->av[2]);
		sim->philo_data[i].time_to_eat = ft_atoi(sim->av[3]);
		sim->philo_data[i].time_to_sleep = ft_atoi(sim->av[4]);
		sim->philo_data[i].tenedores = sim->tenedores;
		sim->philo_data[i].start_time = sim->start_time;	// Momento del inicio del programa
		sim->philo_data[i].meal_counter = 0;
		sim->philo_data[i].last_meal_time = get_time_in_ms();
		if (sim->ac == 6)
			sim->philo_data[i].times_each_philo_must_eat = ft_atoi(sim->av[5]);
		else
			sim->philo_data[i].times_each_philo_must_eat = -1;
		pthread_mutex_init(&sim->philo_data[i].meal_mutex, NULL);
		pthread_create(&sim->philosophers[i], NULL, philosopher, &sim->philo_data[i]);
		i++;
	}
}

void	create_monitor_threads(t_simulation *sim)
{
	pthread_t	monitor_philosophers_thread;
	pthread_t	monitor_meals_thread;

	pthread_create(&monitor_philosophers_thread, NULL, monitor_philosophers, sim->philo_data);
	if (sim->philo_data[0].times_each_philo_must_eat > 0)
		pthread_create(&monitor_meals_thread, NULL, monitor_meals, sim->philo_data);
}

int allocate_resources(t_simulation *sim)
{
	sim->number_of_philosophers = ft_atoi(sim->av[1]);
	sim->philo_data = malloc(sizeof(t_philo_data) * sim->number_of_philosophers);
	sim->philosophers = malloc(sizeof(pthread_t) * sim->number_of_philosophers);
	sim->tenedores = malloc(sizeof(pthread_mutex_t) * sim->number_of_philosophers);

	if (!sim->philosophers || !sim->tenedores || !sim->philo_data)
	{
		printf("Error trying to allocate memory.\n");
		free(sim->philosophers);
		free(sim->tenedores);
		free(sim->philo_data);
		return (1);
	}
	return (0);
}
int	main(int ac, char **av)
{
	t_simulation	sim;
	int				i;

	sim.ac = ac;
	sim.av = av;
	/* sim.number_of_philosophers = ft_atoi(av[1]);
	sim.philo_data = NULL;           // Asegurarse de que esté NULL antes de la asignación
	sim.philosophers = NULL;
	sim.tenedores = NULL; */
	gettimeofday(&sim.start_time, NULL);
	// Verificar si los parámetros son correctos
	if (check_errors(ac, av))
		return (1);
	if (allocate_resources(&sim))
		return (1);

	i = 0;
	// Inicializar los mutex (tenedores)
	while (i < sim.number_of_philosophers)
		pthread_mutex_init(&sim.tenedores[i++], NULL);

	create_threads(&sim);
	create_monitor_threads(&sim);


	i = 0;
	// Esperar a que los hilos terminen (nunca pasa, ya que es un bucle infinito (?))
	while (i < sim.number_of_philosophers)
		pthread_join(sim.philosophers[i++], NULL);

	i = 0;
	// Destruir los mutex (nunca se llega aquí (?))
	while (i < sim.number_of_philosophers)
		pthread_mutex_destroy(&sim.tenedores[i++]);

	// Liberar memoria después de usarla
	free(sim.philo_data);
	free(sim.philosophers);
	free(sim.tenedores);

	return (0);
}
