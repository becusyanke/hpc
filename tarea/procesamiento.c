#include <stdio.h>
#include <math.h>
#include "defs.h"

void genera_seno( float seno[] ) {
	register int n;
	float f = 1000, fs = 15000;

	for (n=0; n<MUESTRAS; n++) {
		seno[n] = sinf( 2 * M_PI * n * f / fs );
	}
}

void genera_hamming( float hamming[] ) {
	register int n;

	for (n=0; n<MUESTRAS; n++) {
		hamming[n] = 0.53836 - (0.46164) * cosf( 2 * M_PI * n / ( MUESTRAS -1 ) );
	}

}
