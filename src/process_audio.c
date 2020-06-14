#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include "process_audio.h"

WAVE *read_wav(char *filename){
	// Open file for reading and if it failed tell the teacher.
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) return NULL;

	// Find the length of the file
	fseek(fp, 0L, SEEK_END);
	int wav_size = ftell(fp);
	rewind(fp);

	// Allocate enough memory to fit the file and allow checking the
	// header without buffer overflow and copy over and close the file.
	char *wav_file = malloc(wav_size + 44);
	if (!wav_file) return NULL; // Sometimes, it won't fit in memory
	fread(wav_file, 1, wav_size, fp);
	fclose(fp);

	// Check if the file is actually a WAV file.
	// I only want to support WAV files with no compression. Otherwise it is way too much work.
	if ((strncmp("WAVE", wav_file + 8, 4) != 0) || (*((uint16_t*)(wav_file + 20)) != 1)) {
		errno = -1;
		return NULL;
	}

	// The output data structure
	WAVE *ret = (WAVE*)malloc(sizeof(WAVE));
	// Safety on the malloc. WAVE is pretty small so it's usually not an issue, but saftey first!
	if (!ret) return NULL;

	// Get some metadata
	ret->name = filename;
	ret->num_channels = *((uint16_t*)(wav_file + 22));
	ret->sample_rate = *((uint32_t*)(wav_file + 24));
	ret->bits_per_sample = *((uint16_t*)(wav_file + 34));
	
	// Search through the chunks until we find the 'data' chunk, usually it's first, but just to be safe.
	int wp = 36;
	while (strncmp("data", wav_file + wp, 4) != 0) {
		wp += 8 + (*((uint32_t*)(wav_file + 4)));
		if (wp > wav_size) NULL;
	}

	// Get the total number of samples and add a pointer to the data itself to the data structure.
	// A benefit of this is that we only have to load the file into memory once!
	ret->num_samples = (*((uint32_t*)(wav_file + wp + 4)))/((ret->bits_per_sample/8) * ret->num_channels);
	ret->data = wav_file + wp + 8;

	return ret;
}

// Terrible function for checking the validity of my read function
void playback(WAVE *wav){
	int num_bytes = (wav->num_channels)*(wav->num_samples)*(wav->bits_per_sample)/8;
	fwrite(wav->data,1,num_bytes,stdout);
}

void debug_WAVE(WAVE *wav){
	printf ("name: %s\n", wav->name);
	printf ("num_channels: %d\n", wav->num_channels);
	printf ("sample_rate: %d\n", wav->sample_rate);
	printf ("bits_per_sample: %d\n", wav->bits_per_sample);
	printf ("num_samples: %d\n", wav->num_samples);
}

int process_audio(char *filename){
	// This page is a stub.
	return 0;
}
