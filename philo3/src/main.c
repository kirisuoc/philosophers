/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erikcousillas <erikcousillas@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:26:27 by erikcousill       #+#    #+#             */
/*   Updated: 2025/02/18 04:04:33 by erikcousill      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_errors(int ac, char **av)
{
	int	times_each_philo_must_eat;

	times_each_philo_must_eat = -1;
	if (ac < 5 || ac > 6)
	{
		printf("Use: %s number_of_philosophers time_to_die time_to_eat \
			time_to_sleep [times_each_philo_must_eat]\n", av[0]);
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

int	allocate_resources(t_simulation *sim)
{
	sim->number_of_philos = ft_atoi(sim->av[1]);
	sim->philo_data = malloc(sizeof(t_philo_data) * sim->number_of_philos);
	sim->philosophers = malloc(sizeof(pthread_t) * sim->number_of_philos);
	sim->tenedores = malloc(sizeof(pthread_mutex_t) * sim->number_of_philos);
	if (!sim->philosophers || !sim->tenedores || !sim->philo_data)
	{
		printf("Error trying to allocate memory.\n");
		if (sim->philo_data)
			free(sim->philo_data);
		if (sim->philosophers)
			free(sim->philosophers);
		if (sim->tenedores)
			free(sim->tenedores);
		return (1);
	}
	return (0);
}

void	*philosopher(void *arg)
{
	t_philo_data	*data;

	data = (t_philo_data *)arg;
	while (1)
	{
		take_forks_and_eat(data);
		to_sleep_and_think(data);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_simulation	sim;
	int				i;

	sim.ac = ac;
	sim.av = av;
	if (check_errors(ac, av))
		return (1);
	gettimeofday(&sim.start_time, NULL);
	if (allocate_resources(&sim))
		return (1);
	i = 0;
	while (i < sim.number_of_philos)
		pthread_mutex_init(&sim.tenedores[i++], NULL);
	create_threads(&sim);
	create_monitor_threads(&sim);

 	i = 0;
	while (i < sim.number_of_philos)
		pthread_join(sim.philosophers[i++], NULL);
	i = 0;
	while (i < sim.number_of_philos)
		pthread_mutex_destroy(&sim.tenedores[i++]);
	free(sim.philo_data);
	free(sim.philosophers);
	free(sim.tenedores);
	return (0);


	return (0);
}
