/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erikcousillas <erikcousillas@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:17:50 by ecousill          #+#    #+#             */
/*   Updated: 2025/02/10 11:54:50 by erikcousill      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct	s_philo_data
{
	int				id;	// ID del filósofo
	int				meal_counter;
	long			last_meal_time;	// Almacena el momento de la última comida
	struct timeval	start_time;
	int				number_of_philosophers;	// Número de filósofos
	int				time_to_die;	// Tiempo para morir sin comer
	int				time_to_eat;	// Tiempo para comer
	int				time_to_sleep;	// Tiempo para dormir
	int				times_each_philo_must_eat;
	pthread_mutex_t	*tenedores;	// Puntero al array de mutex de los tenedores
	pthread_mutex_t	meal_mutex;	// Mutex para proteger meal_counter
}				t_philo_data;

typedef struct	s_simulation
{
	int				number_of_philosophers;
	t_philo_data	*philo_data;
	pthread_t		*philosophers;
	pthread_mutex_t	*tenedores;
	struct timeval	start_time;
	char			**av;
	int				ac;
}				t_simulation;


// utils.c
int		ft_atoi(const char *nptr);
long	get_elapsed_ms(struct timeval *start_time);
long	get_time_in_ms(void);

// monitor.c
void	*monitor_meals(void *arg);
void	*monitor_philosophers(void *arg);

// status.c
void	*take_forks_and_eat(t_philo_data *data, int id);
//void	*to_eat(t_philo_data *data, int id);
void	*to_sleep(t_philo_data *data, int id);
void	*to_think(t_philo_data *data, int id);

#endif
