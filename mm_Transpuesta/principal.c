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

//librerías necesarias para la ejecución del programa
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "biblio.h"


#define DATA_SIZE (1024*1024*64*3) 
static double MEM_CHUNK[DATA_SIZE]; // Reserva de memoria
double *mA, *mB, *mC; // Punteros a las matrices A, B y C
struct timeval start, stop; // Variables para medir el tiempo de ejecución
pthread_mutex_t MM_mutex; // Definición del mutex para controlar acceso a la matriz

int main(int argc, char *argv[]) {
	if (argc < 2) { // Control de argumentos
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
		return -1;
	}
	int SZ = atoi(argv[1]);        // Tamaño de las matrices
	int n_threads = atoi(argv[2]); // Número de hilos

	pthread_t p[n_threads]; // Arreglo de identificadores de hilo
	pthread_attr_t atrMM;   // Atributos del hilo

	mA = MEM_CHUNK; // Asigna la memoria para la matriz A
	mB = mA + SZ * SZ; // Asigna la memoria para la matriz B
	mC = mB + SZ * SZ; // Asigna la memoria para la matriz 

	llenar_matriz(SZ);    // Llena las matrices A y B con datos
	print_matrix(SZ, mA); // Imprime la matriz A
	print_matrix(SZ, mB); // Imprime la matriz B

	inicial_tiempo();                    // Inicia la medición del tiempo
	pthread_mutex_init(&MM_mutex, NULL); // Inicializa el mutex
	pthread_attr_init(&atrMM);           // Inicializa los atributos del hilo
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE); // Establece los atributos para permitir la espera de los hilos creados

	for (int j = 0; j < n_threads; j++) {
		struct parametros *datos = (struct parametros *)malloc(sizeof(
				struct parametros)); // Asigna memoria para la estructura de parámetros
		datos->idH = j;          // Asigna el ID del hilo
		datos->nH = n_threads;   // Asigna el número total de hilos
		datos->N = SZ;           // Asigna el tamaño de las matrices
		pthread_create(&p[j], &atrMM, mult_thread, (void *)datos); // Crea un hilo con los parámetros dados
	}

	for (int j = 0; j < n_threads; j++)
		pthread_join(p[j],NULL); // Espera a que todos los hilos terminen su ejecución
	final_tiempo(); // Finaliza la medición del tiempo e imprime el resultado

	print_matrix(SZ, mC); // Imprime la matriz resultado C si es pequeña

	pthread_attr_destroy(&atrMM);     // Destruye los atributos del hilo
	pthread_mutex_destroy(&MM_mutex); // Destruye el mutex
	pthread_exit(NULL); // Termina el hilo principal y todos los hilos restantes
}