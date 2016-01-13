#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>

#include "DFE.h"
#include <MaxSLiCInterface.h>

#include "nrutil.h"

#define MAXBIT 30
#define	MAXDIM 6

void timeStart(double *timeV){
	struct timeval timeV; 
    gettimeofday(&timeV, NULL); 
    *timeV -= timeV.tv_sec + timeV.tv_usec * 1e-6; 

}
void timeStop(double *timeV){
	struct timeval timeV; 
    gettimeofday(&timeV, NULL); 
    *timeV += timeV.tv_sec + timeV.tv_usec * 1e-6; 
}


void sobseqCPU(int *n, float *x) {
	int j, k, l;
	unsigned long i, im, ipp;

	static float facCPU;
	static unsigned long inCPU, ixCPU[MAXDIM + 1], *iuCPU[MAXBIT + 1];
	static unsigned long mdegCPU[MAXDIM + 1] = {0, 1, 2, 3, 3, 4, 4};
	static unsigned long ipCPU[MAXDIM + 1] = {0, 0, 1, 1, 2, 1, 4};
	static unsigned long ivCPU[MAXDIM * MAXBIT + 1] = {0,1,1,1,1,1,1,3,1,3,3,1,1,5,7,7,3,3,5,15,11,5,15,13,9};

	if (*n < 0) {
		for (k = 1; k <= MAXDIM; k++)
			ix[k] = 0;

		in = 0;

		if (iv[1] != 1) return;

		fac = 1.0 / (1L << MAXBIT);

		for (j = 1, k = 0; j <= MAXBIT; j++, k+= MAXDIM)
			iu[j] = &iv[k];

		for (k = 1; k <= MAXDIM; k++) {
			for (j = 1; j <= mdeg[k]; j++)
				iu[j][k] <<= (MAXBIT - j)

			for (j = mdeg[k]+1; j <= MAXBIT; j++) {
				ipp = ip[k];
				i = iu[j - mdeg[k]][k];
				i ^= (i >> mdeg[k]);

				for (l = mdeg[k]-1; l >= 1; l--) {
					if (ipp & 1) i ^= iu[j-l][k];
					ipp >>= 1;
				}

				iu[j][k] = i;
			}
		}

	}
	else {
		im = in++;
		
		for (j = 1; j <= MAXBIT; j++) {
			if (!(im & 1)) break;
			im >>= 1;
		}

		if (j > MAXBIT) nrerror("MAXBIT too small in sobseq");

		im = (j-1) * MAXDIM;

		for (k = 1; k <= IMIN(*n, MAXDIM); k++) {
			ix[k] ^= iv[im+k];
			x[k] = ix[k] * fac;
		}

	}

}

void sobseq(int *n, float *x) {
	int j, k, l;
	unsigned long i, im, ipp;

	double *timeVal;

	static float fac;
	static unsigned long in, ix[MAXDIM + 1], *iu[MAXBIT + 1];
	static unsigned long mdeg[MAXDIM + 1] = {0, 1, 2, 3, 3, 4, 4};
	static unsigned long ip[MAXDIM + 1] = {0, 0, 1, 1, 2, 1, 4};
	static unsigned long iv[MAXDIM * MAXBIT + 1] = {0,1,1,1,1,1,1,3,1,3,3,1,1,5,7,7,3,3,5,15,11,5,15,13,9};

	if (*n < 0) {
		for (k = 1; k <= MAXDIM; k++)
			ix[k] = 0;

		in = 0;

		if (iv[1] != 1) return;

		fac = 1.0 / (1L << MAXBIT);

		for (j = 1, k = 0; j <= MAXBIT; j++, k+= MAXDIM)
			iu[j] = &iv[k];

		for (k = 1; k <= MAXDIM; k++) {
			for (j = 1; j <= mdeg[k]; j++)
				iu[j][k] <<= (MAXBIT - j)

			for (j = mdeg[k]+1; j <= MAXBIT; j++) {
				ipp = ip[k];
				i = iu[j - mdeg[k]][k];
				i ^= (i >> mdeg[k]);

				for (l = mdeg[k]-1; l >= 1; l--) {
					if (ipp & 1) i ^= iu[j-l][k];
					ipp >>= 1;
				}

				iu[j][k] = i;
			}
		}

	}
	else {
		im = in++;
		
		for (j = 1; j <= MAXBIT; j++) {
			if (!(im & 1)) break;
			im >>= 1;
		}

		if (j > MAXBIT) nrerror("MAXBIT too small in sobseq");

		im = (j-1) * MAXDIM;

		DFE(size, input, countOneOut, countTwoOut, result);

	}

}


int main()
{
	int size = 1024;
	int init = -1;
	int sizeBytes = size * sizeof(float);
	float *x = malloc(sizeBytes);


	timeStart(timeV);
		sobseq(&init, x);
		sobseq(&size, x);
	timeStop(timeV);
	printf("CPU time: %lf",timeV);

	timeStart(timeV);
		sobseqCPU(&init, x);
		sobseqCPU(&size, x);
	timeStop(timeV);
	printf("CPU time: %lf",timeV);


	return null;
}
