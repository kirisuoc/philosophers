#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5
#define TIEMPO_COMER 200000  // Tiempo en microsegundos (0.2 segundos)
#define TIEMPO_PENSAR 300000 // Tiempo en microsegundos (0.3 segundos)
#define TIEMPO_DORMIR 200000 // Tiempo en microsegundos (0.2 segundos)

pthread_mutex_t tenedores[NUM_FILOSOFOS];

// Función para simular pensar, comer y dormir
void *filosofo(void *arg) {
	int id = *(int *)arg;
	int tenedor_izq = id; // Tenedor a la izquierda del filósofo
	int tenedor_der = (id + 1) % NUM_FILOSOFOS; // Tenedor a la derecha

	while (1) {
		// Pensar
		printf("Filósofo %d está pensando.\n", id);
		usleep(TIEMPO_PENSAR);

		// Intentar comer
		printf("Filósofo %d tiene hambre.\n", id);

		// Tomar los tenedores (bloquear mutex)
		pthread_mutex_lock(&tenedores[tenedor_izq]);
		pthread_mutex_lock(&tenedores[tenedor_der]);

		// Comer
		printf("Filósofo %d está comiendo.\n", id);
		usleep(TIEMPO_COMER);

		// Soltar los tenedores (desbloquear mutex)
		pthread_mutex_unlock(&tenedores[tenedor_der]);
		pthread_mutex_unlock(&tenedores[tenedor_izq]);

		// Dormir
		printf("Filósofo %d está durmiendo.\n", id);
		usleep(TIEMPO_DORMIR);
	}
	return NULL;
}

int main() {
	pthread_t filosofos[NUM_FILOSOFOS];
	int ids[NUM_FILOSOFOS];

	// Inicializar los mutex (tenedores)
	for (int i = 0; i < NUM_FILOSOFOS; i++) {
		pthread_mutex_init(&tenedores[i], NULL);
	}

	// Crear los hilos (filósofos)
	for (int i = 0; i < NUM_FILOSOFOS; i++) {
		ids[i] = i;
		pthread_create(&filosofos[i], NULL, filosofo, &ids[i]);
	}

	// Esperar a que los hilos terminen (nunca pasa, ya que es un bucle infinito)
	for (int i = 0; i < NUM_FILOSOFOS; i++) {
		pthread_join(filosofos[i], NULL);
	}

	// Destruir los mutex (nunca se llega aquí)
	for (int i = 0; i < NUM_FILOSOFOS; i++) {
		pthread_mutex_destroy(&tenedores[i]);
	}

	return 0;
}
