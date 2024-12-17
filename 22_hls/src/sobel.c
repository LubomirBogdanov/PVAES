#include "sobel.h"

void gradient(const uint8_t *a1, const uint8_t *a2, const uint8_t *a3, const uint8_t *a4, const uint8_t *a5, const uint8_t *a6, int8_t *output){
	*output = ( ((*a4)+((*a5)<<1)+(*a6)) - ((*a1)+((*a2)<<1)+(*a3)) );
}

void abs_val(const int8_t *x, const int8_t *y, uint8_t *output){
	*output = ((abs(*x)+abs(*y))/4);
}

void threshold(const uint8_t *x, uint8_t *output){
	if( *x > 16 )
		*output = 0;
	else
		*output = 255;
}

void sobel(uint8_t image_in[240][320], uint8_t image_out[240][320]){
#pragma HLS INTERFACE m_axi depth=76800 port=image_out offset=slave	bundle=DATA_IN_OUT_BUS
#pragma HLS INTERFACE m_axi depth=76800 port=image_in offset=slave bundle=DATA_IN_OUT_BUS
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS

	int i, j;
	uint8_t av[240][320];
	int8_t Jx[240][320];
	int8_t Jy[240][320];

	for (j=1; j < 239; j++) {
		for (i=1; i < 319; i++) {
			gradient(&image_in[j-1][i-1], &image_in[j][i-1],
					&image_in[j+1][i-1], &image_in[j-1][i+1], &image_in[j][i+1], &image_in[j+1][i+1], &Jx[j][i]);
		}
	}

	for (j=1; j < 239; j++) {
		for (i=1; i < 319; i++) {
			gradient( &image_in[j-1][i-1], &image_in[j-1][i], &image_in[j-1][i+1], &image_in[j+1][i-1], &image_in[j+1][i], &image_in[j+1][i+1], &Jy[j]
																																				  [i] );
		}
	}

	for (j=1; j < 239; j++) {
		for (i=1; i < 319; i++) {
			abs_val( &Jx[j][i], &Jy[j][i], &av[j][i] );
			threshold( &av[j][i], &av[j][i] );
		}
	}

	for (j=1; j < 239; j++) {
		for (i=1; i < 319; i++) {
			image_out[j][i] = av[j][i];
		}
	}
}
