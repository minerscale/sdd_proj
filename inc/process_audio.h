#ifndef PROCESS_AUDIO_H
#define PROCESS_AUDIO_H

#include <stdint.h>

typedef struct WAVE{
	char     *name;
	uint16_t num_channels;
	uint32_t sample_rate;
	uint16_t bits_per_sample;
	uint32_t num_samples;
	char     *base_ptr;
	char     *data;
} WAVE;

WAVE *read_wav(char *filename);
void debug_WAVE(WAVE *wav);
void playback(WAVE *wav);
void destroy_WAVE(WAVE *wav);
float *WAVE_to_float(WAVE *wav, int channel);
char *float_to_raw(int num_samples, int num_channels, float **data);
int export_WAVE(WAVE *wav);
int process_audio(WAVE *wav_in, WAVE *wav_out, int function);

#endif // PROCESS_AUDIO_H
