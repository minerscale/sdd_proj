#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "process_audio.h"
#include "sound_functions.h"
#include "error.h"

int main(int argc, char *argv[]){
	// Have we supplied an argument?
	if (argc == 4) {

		// Read the WAVE file out
		WAVE *wav = read_wav(argv[2]);
		if (wav == NULL){
			throw(errno);
			return errno;
		}

		// Create the output WAVE struct
		WAVE *wav_out = malloc(sizeof(WAVE));
		if (wav_out == NULL){
			throw(errno);
			return errno;
		}

		// Set the name of the struct to the input
		wav_out->name = argv[3];

		// Convert the input string into an integer
		int function_index = atoi(argv[1]);
		// If it's too big complain and exit
		if (function_index > 3 || function_index <= 0){
			throw(-3);
			return -3;
		}

		// Do the action to the audio
		int err = process_audio(wav, wav_out, function_index - 1);
		if (err != 0){
			throw(err);
			return err;
		}

		// Write the audio to disk
		err = export_WAVE(wav_out);
		if (err != 0){
			throw(err);
			return err;
		}

		// Clear all memory before quitting.
		destroy_WAVE (wav);
		destroy_WAVE (wav_out);
	}

	// If we haven't supplied an argument print the help.
	else {
		printf("Usage: %s ACTION SOURCE DEST\n"
			   "Possible values for ACTION:\n"
			   "    1: quicksort the data\n"
			   "    2: sqrt the data\n"
			   "    3: reverse the data\n"
			   "Example: %s 1 in.wav out.wav\n", argv[0], argv[0]);
	}
}
