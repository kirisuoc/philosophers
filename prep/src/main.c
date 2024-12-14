/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erikcousillas <erikcousillas@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:06:37 by ecousill          #+#    #+#             */
/*   Updated: 2024/12/14 12:05:36 by erikcousill      ###   ########.fr       */
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



/* void	*print_hilo(void *arg)
{
	int	id = *(int *)arg;	// Convertimos el argumento de puntero a void a puntero a int

	printf("¡Hola desde el hilo %d\n", id);
	return NULL;
} */
/* void	*print_hilo(void *arg)
{
	int			counter;	// Convertimos el argumento de puntero a void a puntero a int

	counter = *(int *)arg;

	printf("¡Hola desde el hilo %d\n", counter++);
	return NULL;
} */

typedef struct
{
	int	*counter;			// Puntero al contador compartido
	pthread_mutex_t	*mutex;	// Puntero al mutex
}		hilo_args_t;


void *print_hilo(void *arg) {
	hilo_args_t *args = (hilo_args_t *)arg;

	pthread_mutex_lock(args->mutex); // Bloquear el mutex
	(*(args->counter))++;
	printf("¡Hola desde el hilo %d!\n", *(args->counter));
	pthread_mutex_unlock(args->mutex); // Liberar el mutex

	return NULL;
}

int	main(void)
{
	const int			NUM_HILOS = 5;
	pthread_t			hilos[NUM_HILOS];
	int					counter;
	pthread_mutex_t		mutex = PTHREAD_MUTEX_INITIALIZER;
	hilo_args_t args = { &counter, &mutex }; // Argumentos para los hilos

	counter = 0;

	for (int i = 0; i < NUM_HILOS; i++)
	{
		if (pthread_create(&hilos[i], NULL, print_hilo, &args) != 0)
		{
			perror("Error al crear el hilo.");
			return (1);
		}
	}

	// Esperar a que los hilos terminen
	for (int i = 0; i < NUM_HILOS; i++)
	{
		if (pthread_join(hilos[i], NULL) != 0) // Espera que el hilo termine
		{
			perror("Error al unir el hilo.");
			return (1);
		}
	}

	pthread_mutex_destroy(&mutex); // Destruir el mutex

	// pthread_detach(hilo); // Se separa el hilo y no se necesita hacer pthread_join
	return (0);
}


			// OTRO EJEMPLO

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Inicializamos el mutex

int counter = 0; // Recurso compartido

void *increment_counter(void *arg) {
	for (int i = 0; i < 10000; i++) {
		pthread_mutex_lock(&mutex);    // Bloquea el mutex
		counter++;                    // Sección crítica
		pthread_mutex_unlock(&mutex); // Libera el mutex
	}
	return NULL;
}

int main(void) {
	pthread_t hilo1, hilo2;

	// Crear hilos
	pthread_create(&hilo1, NULL, increment_counter, NULL);
	pthread_create(&hilo2, NULL, increment_counter, NULL);

	// Esperar a que los hilos terminen
	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);

	printf("Valor final del contador: %d\n", counter);

	pthread_mutex_destroy(&mutex); // Destruir el mutex
	return 0;
}
