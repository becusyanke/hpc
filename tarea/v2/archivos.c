#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

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

