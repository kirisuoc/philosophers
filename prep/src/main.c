/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:06:37 by ecousill          #+#    #+#             */
/*   Updated: 2024/12/13 15:46:55 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// pthread_create
// Crea un nuevo hilo de ejecución en un programa
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

// pthread_detach
// Separa un hilo de su proceso principal, lo que el hilo no será seguido ni esperando su terminación por el hilo principal.
// Una vez que un hilo es separado, los recursos asociados a él se liberan automáticamente cuando termina.
// int pthread_detach(pthread_t thread);

// pthread_join
// Espera a que un hilo termine su ejecución. El hilo que llama a pthread_join se bloquea hasta que el hilo especificado finalice.
// int pthread_join(pthread_t thread, void **retval);

// pthread_mutex_init
// Inicializa un mutex (mutual exclusion), que es una herramienta de sincronización usada para evitar condiciones
// de carrera (race conditions) en programas multihilo.
// int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);

// pthread_mutex_destroy
// Destruye un mutex previamente inicializado con pthread_mutex_init. Es importante liberar los recursos del mutex
// una vez que ya no se necesita.
// int pthread_mutex_destroy(pthread_mutex_t *mutex);

// pthread_mutex_lock
// Bloquea un mutex, lo que significa que el hilo que lo llama no puede continuar hasta que el mutex esté disponible (es decir,
// no esté bloqueado por otro hilo.)
// int pthread_mutex_lock(pthread_mutex_t *mutex);

// pthread_mutex_unlock
// Desbloquea un mutex, lo que permite que otros hilos puedan adquirirlo y continuar su ejecución.
// int pthread_mutex_unlock(pthread_mutex_t *mutex);

// RESUMEN
/*
pthread_create: Crea un nuevo hilo.
pthread_detach: Separa un hilo, de modo que no se requiere hacer pthread_join.
pthread_join: Espera que un hilo termine su ejecución.
pthread_mutex_init: Inicializa un mutex.
pthread_mutex_destroy: Destruye un mutex.
pthread_mutex_lock: Bloquea un mutex.
pthread_mutex_unlock: Desbloquea un mutex.
*/

void	*mi_funcion(void *arg)
{
	printf("Hilo en ejecución\n");
	return (NULL);
}

int	main(void)
{
	pthread_t hilo;

	pthread_create(&hilo, NULL, mi_funcion, NULL);

	// pthread_join(hilo, NULL); // Espera que el hilo termine

	pthread_detach(hilo); // Se separa el hilo y no se necesita hacer pthread_join
	return (0);
}
