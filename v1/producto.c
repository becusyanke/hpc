#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 16

int * reservar_memoria( void );
void llenar_arreglo(int *datos);
void imprimir_arreglo( int *datos );
void producto( void );

int *A, *B, *P;

int main() {

	A  = reservar_memoria();
	llenar_arreglo( A );
	imprimir_arreglo( A );

	B  = reservar_memoria();
	llenar_arreglo( B );
	imprimir_arreglo( B );

	P  = reservar_memoria();
	producto();
	imprimir_arreglo( P );

	return 0;
}

void producto( void ) {
	register int i;

	for(i=0; i<N ; i++)
		P[i]=A[i] * B[i];
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
