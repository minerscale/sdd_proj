//#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "error.h"
#include "process_audio.h"

WAVE read_wav(char *filename){
	// The output data structure
	struct WAVE ret;

	// Open file for reading
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) throw("could not open file for reading", 2);

	// Find the length of the file
	fseek(fp, 0L, SEEK_END);
	int wav_size = ftell(fp);
	rewind(fp);

	// Allocate just enough memory to fit the file in, copy over and close the file
	char *wav_file = malloc(wav_size + 1);
	fread(wav_file, 1, wav_size, fp);
	fclose(fp);

	// Check if the file is actually a WAV file.
	if (strncmp("WAVE", wav_file + 8, 4) != 0) throw("invalid .wav file", 3);

	// I only want to support WAV files with no compression. Otherwise it is way too much work.
	if (*((uint16_t*)(wav_file + 20)) != 1) throw("invalid .wav file", 3);

	// Get some metadata
	ret.name = filename;
	ret.num_channels = *((uint16_t*)(wav_file + 22));
	ret.sample_rate = *((uint32_t*)(wav_file + 24));
	ret.bits_per_sample = *((uint16_t*)(wav_file + 34));
	
	// Search through the chunks until we find the 'data' chunk, usually it's first, but just to be safe.
	int wp = 36;
	while (strncmp("data", wav_file + wp, 4) != 0) {
		wp += 8 + (*((uint32_t*)(wav_file + 4)));
		if (wp > wav_size) throw("invalid .wav file", 3);
	}

	// Get the total number of samples and add a pointer to the data itself to the data structure.
	// A benefit of this is that we only have to load the file into memory once!
	ret.num_samples = (*((uint32_t*)(wav_file + wp + 4)))/((ret.bits_per_sample/8) * ret.num_channels);
	ret.data = wav_file + wp + 8;

	return ret;
}

void debug_WAVE(WAVE wav){
	printf ("name: %s\n", wav.name);
	printf ("num_channels: %d\n", wav.num_channels);
	printf ("sample_rate: %d\n", wav.sample_rate);
	printf ("bits_per_sample: %d\n", wav.bits_per_sample);
	printf ("num_samples: %d\n", wav.num_samples);
}

int process_audio(char *filename){
	return 0;
}
