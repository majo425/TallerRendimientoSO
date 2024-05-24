/**************************************************************
	Pontificia Universidad Javeriana
	Autores:   María José Cárdenas Machaca, Juan Diego Palacios Toledo, Andrés Leonardo Manrique Hernández, Juan Pablo Hernández Ceballos
	Fecha: 09 mayo 2024
	Materia: Sistemas Operativos
	Tema: Taller de Evaluación de Rendimiento
	Fichero: fuente de multiplicación de matrices NxN por hilos.
	Objetivo: Evaluar el tiempo de ejecución del 
		      algoritmo clásico de multiplicación de matrices.
			  Se implementa con la Biblioteca POSIX Pthreads
****************************************************************/
#ifndef __BIBLIO_H__
#define __BIBLIO_H__

#include <pthread.h>

struct parametros {
	int nH;  // Número total de hilos
	int idH; // Identificador del hilo actual
	int N;   // Tamaño de las matrices cuadradas NxN
};

/*Se hacen las siguientes definiciones con extern para que no haya conflicto
con la función principal.
*/
extern double *mA, *mB, *mC; // Punteros a las matrices A, B y C
extern struct timeval start, stop; // Variables para medir el tiempo de ejecución
extern pthread_mutex_t MM_mutex;// Definición del mutex para controlar acceso a la matriz

// Función para llenar las matrices A y B 
void llenar_matriz(int SZ);

// Función para imprimir una matri
void print_matrix(int sz, double *matriz);

// Función para iniciar la medición del tiempo
void inicial_tiempo();

// Función para finalizar la medición del tiempo e imprimir el resultado
void final_tiempo();

// Función para la multiplicación de matrices
void *mult_thread(void *variables);

#endif
