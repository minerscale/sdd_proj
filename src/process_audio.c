#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <sound_functions.h>

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
	if ((strncmp("WAVE", wav_file + 8, 4) != 0)) {
		errno = -1;
		return NULL;
	} else if ((*((uint16_t*)(wav_file + 20)) != 1)){
		errno = -2;
		return NULL;
	}

	// The output data structure
	WAVE *ret = (WAVE*)malloc(sizeof(WAVE));
	// Safety on the malloc. WAVE is pretty small so it's usually not an issue, but saftey first!
	if (!ret) return NULL;

	ret->base_ptr = wav_file;

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

// Allow for freeing WAVE objects once finished.
void destroy_WAVE(WAVE *wav){
	free(wav->base_ptr);
	free(wav);
}

// Convert raw WAVE struct to a more usable array of floats. NULL if out of memory.
// Channel is the channel to convert, undefined behaviour results if the channel selector is too high.
float *WAVE_to_float(WAVE *wav, int channel){
	// Extract the data to avoid having to dereference the pointers once per loop.
	int num_samples = wav->num_samples;
	int num_channels = wav->num_channels;
	int bits_per_sample = wav->bits_per_sample;

	// Allocate memory for the float array.
	float *ret = (float*)malloc(num_channels * num_samples * sizeof(float));
	if (!ret) return NULL;

	switch(bits_per_sample) {
		// Unsigned 8 bit data
		case 8:
			for (int i = 0; i < num_samples; ++i){
				ret[i] = (wav->data[i*num_channels + channel] / 127.5) - 1;
			}
			break;
		// Signed 16 bit data
		case 16:
			for (int i = 0; i < num_samples; ++i){
				ret[i] = (((int16_t *)(wav->data))[i*num_channels + channel]) / 32767.0;
			}
			break;
		// Signed 24 bit data
		case 24:
			for (int i = 0; i < num_samples; ++i){
				int base_ptr = 3*(i*num_channels + channel);
				ret[i] = (((wav->data[base_ptr] << 24) | (wav->data[base_ptr + 3] << 16) | 
					     (wav->data[base_ptr + 6] << 8)) >> 8)/8388607.0;

			}
			break;
		// Assumes 32 bit float data, I can't figure out how to get the type
		case 32:
			for (int i = 0; i < num_samples; ++i){
				ret[i] = (((int32_t *)(wav->data))[i*num_channels + channel]) / 2147483647.0;
			}
			break;

		// Unable to convert non-standard WAV bitrates
		default:
			errno = -2; // Unsupported WAV format.
			return NULL;
	}

	return ret;
}

// 16 bit WAV export supported only because I'm lazy.
char *float_to_raw(int num_samples, int num_channels, float **data){
	int16_t *ret = malloc(num_samples*num_channels*sizeof(int16_t));
	if (!ret) return NULL;

	for (int i = 0; i < num_samples; ++i){
		for (int j = 0; j < num_channels; ++j){
			ret[num_channels*i + j] = 32767*data[j][i];
		}
	}
	return (char *)ret;
}

int export_WAVE(WAVE *wav){
	char *wav_header = malloc(44);
	if (!wav_header) return errno;
	// Write a scaffold of the data to memory.
	memcpy(wav_header, "RIFF    WAVEfmt                     data", 40);

	// Populate empty parts
	((int32_t *)wav_header)[1] = 36 + (wav->num_samples)*(wav->num_channels)*(wav->bits_per_sample/8);
	((int32_t *)wav_header)[4] = 16;
	((int16_t *)wav_header)[10] = 1;
	((int16_t *)wav_header)[11] = wav->num_channels;
	((int32_t *)wav_header)[6] = wav->sample_rate;
	((int32_t *)wav_header)[7] = (wav->sample_rate)*(wav->num_channels)*(wav->bits_per_sample/8);
	((int16_t *)wav_header)[16] = (wav->num_channels)*(wav->bits_per_sample/8);
	((int16_t *)wav_header)[17] = wav->bits_per_sample;
	((int32_t *)wav_header)[10] = (wav->num_samples)*(wav->num_channels)*(wav->bits_per_sample/8);

	// Write to the file.
	FILE *fp = fopen (wav->name, "wb");
	if (!fp) return errno;
	fwrite(wav_header, 1, 44, fp);

	fwrite(wav->data, 1, (wav->num_samples)*(wav->num_channels)*sizeof(int16_t), fp);
	fclose(fp);

	// Free up unused memory.
	free(wav_header);

	// Return a success.
	return 0;
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

// wav_in must have same basic metadata as wav_out.
int process_audio(WAVE *wav_in, WAVE *wav_out, int function){
	float **data_f = malloc(sizeof(float*) * wav_in->num_channels);

	for (int i = 0; i < wav_in->num_channels; ++i){
		data_f[i] = WAVE_to_float(wav_in, i);
		function_table[function](wav_in->num_samples, data_f[i]);
	}
	
	char *raw_data = float_to_raw(wav_in->num_samples, wav_in->num_channels, data_f);
	if (raw_data == NULL){
		return errno;
	}

	for (int i = 0; i < wav_in->num_channels; ++i){
		free (data_f[i]);
	}
	free(data_f);

	wav_out->bits_per_sample = 16;
	wav_out->num_samples = wav_in->num_samples;
	wav_out->sample_rate = wav_in->sample_rate;
	wav_out->num_channels = wav_in->num_channels;
	wav_out->base_ptr = raw_data;
	wav_out->data = raw_data;

	return 0;
}
