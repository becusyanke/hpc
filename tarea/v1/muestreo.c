#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MUESTRAS 512

void genera_seno( float seno[] );
void guarda_datos( float seno[] );

int main() {
	float seno[MUESTRAS];
	genera_seno( seno );
	guarda_datos( seno );
	return 0;
}

void guarda_datos( float seno[] ) {
	FILE *archivo;
	archivo = fopen("seno.dat", "w");
	register int n;

	if ( !archivo ) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}

	for (n=0; n<MUESTRAS; n++) {
		fprintf(archivo, "%f \n", seno[n]);
	}

	fclose( archivo );
}

void genera_seno( float seno[] ) {
	register int n;
	float f = 1000, fs = 15000;

	for (n=0; n<MUESTRAS; n++) {
		seno[n] = sinf( 2 * M_PI * n * f / fs );
	}
}
