#include <stdio.h>

#include "process_audio.h"
#include "sound_functions.h"

int main(int argc, char *argv[]){
	if (argc >= 2){
		WAVE wav = read_wav(argv[1]);

		debug_WAVE(wav);
	}
}
