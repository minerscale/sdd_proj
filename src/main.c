#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "process_audio.h"
#include "sound_functions.h"
#include "error.h"

int main(int argc, char *argv[]){
	// Have we supplied an argument?
	if (argc == 3) {
		// Create the output WAVE struct
		WAVE *wav_out = malloc(sizeof(WAVE));
		if (wav_out == NULL){
			throw(errno);
			return errno;
		}

		// Set the name of the struct to the input
		wav_out->name = argv[2];

		// Convert the input string into an integer
		int function_index = atoi(argv[1]);
		
		// If it's too big complain and exit
		if (function_index > 2 || function_index <= 0){
			throw(-3);
			return -3;
		}

		float **data_f = process(NUM_SAMPLES, function_index - 1);


		char *raw_data = float_to_raw(NUM_SAMPLES, 2, data_f);

		wav_out->num_channels = 2;
		wav_out->sample_rate = SAMPLE_RATE;
		wav_out->bits_per_sample = 16;
		wav_out->num_samples = NUM_SAMPLES;
		wav_out->base_ptr = raw_data;
		wav_out->data = raw_data;	

		if (function_index == 1){
			// Write the audio to disk
			int err = export_WAVE(wav_out);
			if (err != 0){
				throw(err);
				return err;
			}
		}

		destroy_WAVE (wav_out);
	}

	// If we haven't supplied an argument print the help.
	else {
		printf("Usage: %s ACTION DEST\n"
			   "Possible values for ACTION:\n"
			   "    1: output to a WAV file\n"
			   "    2: spit out the raw data\n"
			   "Example: %s 1 out.wav\n", argv[0], argv[0]);
	}
}
