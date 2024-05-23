/**************************************************************
	Pontificia Universidad Javeriana
	Autores:  
	Fecha: 09 mayo 2024
	Materia: Sistemas Operativos
	Tema: Taller de Evaluación de Rendimiento
	Fichero: fuente de multiplicación de matrices NxN por hilos.
	Objetivo: Evaluar el tiempo de ejecución del 
		      algoritmo clásico de multiplicación de matrices.
			  Se implementa con la Biblioteca POSIX Pthreads
****************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "biblio.h"

/*--- Función para llenar las matrices ---*/
void llenar_matriz(int SZ) {
	srand48(time(NULL));
	for (int i = 0; i < SZ * SZ; i++) {
		mA[i] = 1.1 * i; // Asigna un valor incremental a la matriz A
		mB[i] = 2.2 * i; // Asigna un valor incremental a la matriz B
		mC[i] = 0;       // Inicializa la matriz resultado C con ceros
	}
}

/*-- Función para imprimir una matriz  --*/
void print_matrix(int sz, double *matriz) {
	if (sz < 12) {
		for (int i = 0; i < sz * sz; i++) {
			if (i % sz == 0)
				printf("\n"); // Salto de línea al empezar una nueva fila
			printf(" %.3f ",
						 matriz[i]); // Imprime el elemento de la matriz con tres decimales
		}
	}
	printf(
			"\n>-------------------->\n"); // Separador visual al final de la matriz
}

/*-- Función para iniciar la medición del tiempo --*/
void inicial_tiempo() { 
	gettimeofday(&start, NULL); 
}

/*-- Función para finalizar la medición del tiempo e imprimir el resultado --*/
void final_tiempo() {
	gettimeofday(&stop, NULL);
	stop.tv_sec -= start.tv_sec;
	printf("\n:-> %9.0f µs\n",(double)(stop.tv_sec * 1000000 + stop.tv_usec)); // Imprime el tiempo transcurrido en microsegundos
}

/*-- Función para la multiplicación de matrices --*/
void *mult_thread(void *variables) {
	struct parametros *data = (struct parametros *)variables;

	int idH = data->idH;      // Asigna el ID del hilo actual
	int nH = data->nH;        // Asigna el número total de hilos
	int N = data->N;          // Asigna el tamaño de las matrices NxN
	int ini = (N / nH) * idH; // Calcula el índice inicial para la sección de la
														// matriz a procesar por el hilo actual
	int fin = (N / nH) * (idH + 1); // Calcula el índice final para la sección de
																	// la matriz a procesar por el hilo actual

	for (int i = ini; i < fin; i++) {
		for (int j = 0; j < N; j++) {
			double *pA, *pB, sumaTemp = 0.0;
			pA = mA + (i * N); // Puntero al inicio de la fila i de la matriz A
			pB = mB + (j * N); // Puntero al inicio de la columna j de la matriz B
			for (int k = 0; k < N;
					 k++, pA++, pB++) { // Recorre la fila y la columna para realizar la
															// multiplicación
				sumaTemp +=
						(*pA * *pB); // Acumula el resultado parcial de la multiplicación
			}
			mC[i * N + j] = sumaTemp; // Almacena el resultado en la matriz C
		}
	}

	pthread_mutex_lock(&MM_mutex); // Bloquea el mutex
	pthread_mutex_unlock(&MM_mutex); // Desbloquea el mutex
	pthread_exit(NULL);              // Termina el hilo
}

