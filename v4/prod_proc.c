#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_PROC 2
#define N 16

void proceso_hijo( int np, int pipefd[] );
void proceso_padre( int pipefd[] );
int * reservar_memoria( void );
void llenar_arreglo(int *datos);
void imprimir_arreglo( int *datos );

int *A, *B, *P;

int main() {
	register int np;
	pid_t pid;
	int pipefd[2];

	A = reservar_memoria();
	llenar_arreglo( A );
	imprimir_arreglo( A );

	B = reservar_memoria();
	llenar_arreglo( B );
	imprimir_arreglo( B );

	P = reservar_memoria();

	pipe( pipefd );

	for ( np = 0; np < NUM_PROC; np++) {
		pid = fork();

		if ( pid == -1) {
			perror("Error al generar el proceso");
			exit (EXIT_FAILURE);
		} else if ( !pid ) {
			proceso_hijo( np, pipefd );
		}
	}

	proceso_padre( pipefd  );
	imprimir_arreglo( P );

	free ( A );
	free ( B );
	free ( P );


	return 0;
}

int * reservar_memoria( void ) {
	int *dato;
	dato = (int *)malloc(N * sizeof(int) );
	llenar_arreglo(dato);

	if ( !dato ) {
		perror("Error en la asignacion de memoria");
		exit(EXIT_FAILURE);
	}

	return dato;
}


void llenar_arreglo( int *datos ) {
	register int i;

	for (i = 0; i < N; i++) {
		datos[i] = rand() % 256;
	}
}

void imprimir_arreglo( int *datos ) {
	register int i;

	for (i = 0; i < N; i++) {
		printf("%d ", datos[i]);
		if ( ! ((i+1) % 8)  ) {
			printf("\n");
		}
	}
}

void proceso_hijo( int np, int pipefd[] ) {
	printf("Proceso %d con pid %d ejecutado\n", np, getpid() );

	register int i;
	int bloque, inicio, fin;

	bloque = N / NUM_PROC;
	inicio = np * bloque;
	fin = inicio + bloque;

	for ( i = inicio; i < fin; i++ ) {
		P[i] = A[i] * B[i];
	}

	close( pipefd[0] );
	write( pipefd[1], P+inicio, sizeof(int)*bloque );
	exit( np );
}

void proceso_padre( int pipefd[] ) {
	register int i;
	int np, inicio, bloque;
	bloque = N / NUM_PROC;
	pid_t pid;

	close( pipefd[1] );

	for (i = 0; i < NUM_PROC; i++) {
		pid = wait( &np );
		np = np >> 8;
		inicio = np * bloque;
		read( pipefd[0], P+inicio, sizeof(int)*bloque );
		printf("Proceso con pid %d \n", pid);

	}
}

//Ordenar elementos del arreglo y obtener el promedio de los datos
