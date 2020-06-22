#include <stdlib.h>
#include <math.h>
#include "sound_functions.h"

int float_compare_function(const void *a,const void *b) {
	float *x = (float *) a;
	float *y = (float *) b;

	if (*x < *y) return -1;
	else if (*x > *y) return 1;
	return 0;
}

// In place sort the audio
void sort_audio(int num_samples, float *data){
	qsort(data, num_samples, sizeof(float), float_compare_function);
}

void square_root(int num_samples, float *data){
	for (int i = 0; i < num_samples; ++i){
		data[i] = powf(data[i],1/10.0);
	}
}

void (*function_table[2])(int, float *) = {sort_audio, square_root};
