#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "process_audio.h"
#include "sound_functions.h"
#include "error.h"

int main(int argc, char *argv[]){
	if (argc >= 2){
		WAVE *wav = read_wav(argv[1]);

		if (wav == NULL){
			throw(errno);
			exit(errno);
		}

		debug_WAVE(wav);
	}
}
