#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define NUM_HILOS 4
#define N 16

int * reservar_memoria( void );
void llenar_arreglo(int *datos);
void imprimir_arreglo( int *datos );


void * producto1( void * );
void * producto2( void * );
void * producto3( void * );
void * producto4( void * );

int *A, *B, *P;

int main() {

	pthread_t tids[NUM_HILOS];
	int ids[NUM_HILOS]={0,1,2,3}, rets[NUM_HILOS];

	A  = reservar_memoria();
	llenar_arreglo( A );
	imprimir_arreglo( A );

	B  = reservar_memoria();
	llenar_arreglo( B );
	imprimir_arreglo( B );

	P  = reservar_memoria();
	pthread_create(&tids[0], NULL, producto1, (void*)&ids[0]);
	pthread_create(&tids[1], NULL, producto2, (void*)&ids[1]);
	pthread_create(&tids[2], NULL, producto3, (void*)&ids[2]);
	pthread_create(&tids[3], NULL, producto4, (void*)&ids[3]);

	pthread_join(tids[0], (void *) &rets[0] );	
	pthread_join(tids[1], (void *) &rets[1] );	
	pthread_join(tids[2], (void *) &rets[2] );	
	pthread_join(tids[3], (void *) &rets[3] );	


	imprimir_arreglo( P );

	free(A);
	free(B);
	free(P);
	return 0;
}

void * producto1( void *id) {
	register int i;

	for(i=*(int *)id; i<N ; i+=NUM_HILOS)
		P[i]=A[i] * B[i];

	pthread_exit(id);
}

void * producto2( void *id) {
	register int i;

	for(i=*(int *)id; i<N ; i+=NUM_HILOS)
		P[i]=A[i] * B[i];

	pthread_exit(id);

}

void * producto3( void *id) {
	register int i;

	for(i=*(int *)id; i<N ; i+=NUM_HILOS)
		P[i]=A[i] * B[i];

	pthread_exit(id);

}

void * producto4( void *id) {
	register int i;

	for(i=*(int *)id; i<N ; i+=NUM_HILOS)
		P[i]=A[i] * B[i];
	pthread_exit(id);
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
