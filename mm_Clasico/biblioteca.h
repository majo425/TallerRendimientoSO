	/**************************************************************
	Pontificia Universidad Javeriana
	Autores:  Juan Diego Palacios Toledo, María José Cárdenas Machaca, Andrés Leonardo Manrique Hernández, Juan Pablo Hernández Ceballos
	Fecha: 09 mayo 2024
	Materia: Sistemas Operativos
	Tema: Taller de Evaluación de Rendimiento
	Fichero: Encabezado de la biblioteca de multiplicación de matrices NxN por hilos.
	Objetivo: Evaluar el tiempo de ejecución del 
					algoritmo clásico de multiplicación de matrices.
				Se implementa con la Biblioteca POSIX Pthreads
****************************************************************/
#ifndef __BIBLIOTECA_H__
#define __BIBLIOTECA_H__

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define DATA_SIZE (1024*1024*64*3)

extern pthread_mutex_t MM_mutex; // Declaración del mutex para controlar el acceso a la matriz resultado
extern double *mA, *mB, *mC; // Punteros a las matrices A, B y C
extern pthread_mutex_t MM_mutex;

struct parametros{
	int nH; // Número de hilo
	int idH; // Identificador del hilo actual
	int N; // Tamaño de las matrices cuadradas NxN
};

extern struct timeval start, stop; // Variables para medir el tiempo de ejecución

// Función para llenar las matrices A y B 
void llenar_matriz(int SZ);

// Función para imprimir una matriz
void print_matrix(int sz, double *matriz);

// Función para iniciar la medición del tiempo
void inicial_tiempo();

// Función para finalizar la medición del tiempo e imprimir el resultado
void final_tiempo();

// Función para la multiplicación de matrices
void *mult_thread(void *variables);

#endif