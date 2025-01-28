/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:17:50 by ecousill          #+#    #+#             */
/*   Updated: 2025/01/28 16:44:39 by ecousill         ###   ########.fr       */
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
	int	id;	// ID del filósofo
	int	number_of_philosophers;	// Número de filósofos
	int	time_to_eat;	// Tiempo para comer
	int	time_to_sleep;	// Tiempo para dormir
	pthread_mutex_t *tenedores;	// Puntero al array de mutex de los tenedores
	int	number_of_times_each_philosopher_must_eat;
	int	meal_counter;
	struct timeval start_time;
}				t_philo_data;


// utils.c
int	ft_atoi(const char *nptr);
long get_elapsed_ms(struct timeval start_time);

#endif
