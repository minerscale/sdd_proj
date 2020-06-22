#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "process_audio.h"
#include "sound_functions.h"
#include "error.h"

int main(int argc, char *argv[]){
	//while((int opt = getopt(argc,argv,"o")))

	// Have we supplied an argument?
	if (argc == 4) {
		WAVE *wav = read_wav(argv[2]);

		if (wav == NULL){
			throw(errno);
			return errno;
		}

		WAVE *wav_out = malloc(sizeof(WAVE));

		// Set the name
		wav_out->name = argv[3];

		process_audio(wav, wav_out, atoi(argv[1]));

		export_WAVE(wav_out);

		destroy_WAVE (wav);
		destroy_WAVE (wav_out);
	}
	// If we haven't supplied an argument print the help.
	else {
		printf("Usage: %s VALUE SOURCE DEST\n"
			   "possible values for VALUE:\n"
			   "    0: quicksort the data\n"
			   "    1: sqrt() the data\n", argv[0]);
	}
}
