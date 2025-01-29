/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:17:50 by ecousill          #+#    #+#             */
/*   Updated: 2025/01/29 11:43:31 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct s_philo_data
{
	int				id;	// ID del filósofo
	int				meal_counter;
	long			last_meal_time;	// Almacena el momento de la última comida en ms
	struct timeval	start_time;
	int				number_of_philosophers;	// Número de filósofos
	int				time_to_die;	// Tiempo para morir sin comer
	int				time_to_eat;	// Tiempo para comer
	int				time_to_sleep;	// Tiempo para dormir
	int				number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	*tenedores;	// Puntero al array de mutex de los tenedores
	pthread_mutex_t	meal_mutex;	// Mutex para proteger meal_counter
}				t_philo_data;


// utils.c
int	ft_atoi(const char *nptr);
long get_elapsed_ms(struct timeval start_time);
long get_time_in_ms(void);

#endif
