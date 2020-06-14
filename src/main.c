#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "process_audio.h"
#include "sound_functions.h"
#include "error.h"

int main(int argc, char *argv[]){
	// Have we supplied an argument?
	if (argc >= 2) {
		WAVE *wav = read_wav(argv[1]);

		if (wav == NULL){
			throw(errno);
			return errno;
		}

		float *data_float_c0 = WAVE_to_float(wav, 0);
		float *data_float_c1 = WAVE_to_float(wav, 1);

		float *channel_data[] = {data_float_c0,data_float_c1};

		sort_audio(wav->num_samples, data_float_c0);
		sort_audio(wav->num_samples, data_float_c1);
		
		char *raw_data = float_to_raw(wav->num_samples,wav->num_channels,channel_data);

		free(data_float_c0);
		free(data_float_c1);

		WAVE converted;

		converted.name = "./test.wav";
		converted.num_channels = 2;
		converted.sample_rate = wav->sample_rate;
		converted.bits_per_sample = 16;
		converted.num_samples = wav->num_samples;
		converted.base_ptr = raw_data;
		converted.data = raw_data;

		int err = export_WAVE(&converted);
		if (err){
			throw(err);
			return err;
		}

		debug_WAVE(&converted);

		destroy_WAVE(wav);
		free(converted.base_ptr);
	}
	// If we haven't supplied an argument print the help.
	else {
		printf("Usage: process [OPTION] ... SOURCE DEST\n");
	}
}
