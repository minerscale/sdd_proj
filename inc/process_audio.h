#ifndef PROCESS_AUDIO_H
#define PROCESS_AUDIO_H

#include <stdint.h>

typedef struct WAVE{
	char     *name;
	uint16_t num_channels;
	uint32_t sample_rate;
	uint16_t bits_per_sample;
	uint32_t num_samples;
	char     *data;
} WAVE;

WAVE read_wav(char *filename);
void debug_WAVE(WAVE wav);

#endif // PROCESS_AUDIO_H
