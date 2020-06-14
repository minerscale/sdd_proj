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
		playback(wav);
		printf("sex\n");
		//debug_WAVE(wav);
	}
	// If we haven't supplied an argument print the help.
	else {
		printf("Usage: process [OPTION] ... SOURCE DEST\n");
	}
}
