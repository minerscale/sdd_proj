#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "song.h"
#include "sound_functions.h"

#define TAU 6.2831853
#define R -127

#define TOTAL_VOICES 4
#define INIT_BPS 2

double BPS = INIT_BPS; // 120 bpm
double BEAT_DELTA = (double)INIT_BPS/SAMPLE_RATE;

double timer = 0;
double fundamental = 110;

int file_index = 0;


double sqr(int i){
	return (i%2)?1.0/i:0;
}

double saw(int i){
	return 1.0/i;
}

double tri(int i){
	return (i%2)?( ((i/2)%2)?-1:1) * 1.0/(i*i) :0;
}

typedef struct instrument instrument;
struct instrument {
	double (*partial)(int);
	double a; // Attack
	double d; // Decay
	double s; // Sustain
	double r; // Release
	double bound; // Overtone bound
};

typedef struct note note;
struct note {
	double freq; // Note frequency
	instrument inst; // Timbre/Envelope data
	double held; // How long the note has been held for (in beats)
	double vol; // amplitude of the note
	bool released; // Is the note currently held down?
};

instrument instruments[3] = {
	{sqr, 0.02, 0.1, 0.6, 0.4, 20},
	{saw, 0.02, 0.1, 0.6, 0.4, 20},
	{tri, 0.02, 0.1, 0.6, 0.4, 20},
};

note voices [TOTAL_VOICES];

double organ(int t, double note, double bound, double (*partial)(int)){
	if (note <= 0){
		return 0;
	}
	double input = note*t*TAU/SAMPLE_RATE;

	double sum = 0;
	bound += 1;
	for (int i = 1; i <= (int)bound; ++i){
		sum += ((i==(int)bound)?fmod(bound,1):1) * (*partial)(i)*sin(i*input);
	}

	return sum;
}

void trigger_note(int voice, double freq, double volume){
	voices[voice].held = 0;
	voices[voice].released = false;
	voices[voice].freq = freq;
	voices[voice].vol = volume;
}

void release_note(int voice){
	voices[voice].held = 0;
	voices[voice].released = true;
}

double envelope(double p, double a, double d, double s, double r, bool released){
	if (released == false){
		if (p <= a){
			return p/a;
		} else if (p <= d + a){
			return 1 - (1-s)/d*(p-a);
		} else {
			return s;
		}
	}else{
		if (p <= r){
			return s - (s/r)*(p);
		} else {
			return 0;
		}
	}
}

double play_note(int t, double b, note* cur_note_ptr){
	note cur_note = *cur_note_ptr;
	double env_data = envelope(cur_note.held, cur_note.inst.a, cur_note.inst.d, cur_note.inst.s, cur_note.inst.r, cur_note.released);
	double sample = cur_note.vol * env_data *
		     organ(t, cur_note.freq, cur_note.inst.bound, cur_note.inst.partial);

	cur_note_ptr->held += BEAT_DELTA;

	return sample;
}

void debug_note(note n){
	fprintf(stderr, "freq: %f\n%f\n", n.freq, BEAT_DELTA);
}

// Return whether or not we want to continue processing new commands
bool process_command(unsigned char voice, unsigned char command, float arg){
	bool ret = false;
	switch (command){
		case 1: // Play note of ratio arg of the fundamental
			trigger_note(voice, fundamental*arg, voices[(int)voice].vol);
		break;
		case 2: // Release note (arg unused)
			release_note(voice);
		break;
		case 3: // Set instrument to arg, must do that before playing a note or else a crash
			voices[voice].inst = instruments[(int)arg];
		break;
		case 4: // Set volume to arg
			voices[voice].vol = arg;
		break;
		case 5: // Set tempo (in beats per second) to arg
			BPS = arg;
			BEAT_DELTA = (double)BPS/SAMPLE_RATE;
		break;
		case 6: // Wait for arg beats
			timer = arg;
			ret = true;
		break;
		case 7: // Exit
			exit(0);
		break;
		case 8: // Set fundamental frequency
			fundamental = arg;
		break;
		case 9: // Multiply fundamental by arg
			fundamental *= arg;
		break;
		case 10: // Jump to arg COMMANDS
			file_index = 6*arg;
		break;
		case 11: // Set instrument bound
			voices[voice].inst.bound = arg;
		break;
		case 12: // Set instrument attack
			voices[voice].inst.a = arg;
		break;
		case 13: // Set instrument decay
			voices[voice].inst.d = arg;
		break;
		case 14: // Set instrument sustain
			voices[voice].inst.s = arg;
		break;
		case 15: // Set instrument release
			voices[voice].inst.r = arg;
		break;
	}
	return ret;
}

float **process(int num_samples, int dump){
	float *channel_l = malloc(sizeof(float)*num_samples);
	float *channel_r = malloc(sizeof(float)*num_samples);

	float **ret = malloc(sizeof(float)*num_samples);
	(ret)[0] = channel_l;
	(ret)[1] = channel_r;


	double tick = 0;

	timer = 0;
	fundamental = 110;
	file_index = 0;
	BPS = INIT_BPS; // 120 bpm
	BEAT_DELTA = (double)INIT_BPS/SAMPLE_RATE;

	for (int t = 0;t < num_samples;++t){
		tick += BEAT_DELTA;

		if (timer <= 0){
			while (1){
				unsigned char voice = sound_data[file_index++];
				unsigned char command = sound_data[file_index++];
				float arg = *(float*)(sound_data + file_index);

				file_index += 4;
				if (process_command(voice, command, arg)){
					break;
				}
			}
		}

		double sample = 0;
		for (int v = 0; v < TOTAL_VOICES; v++){
			sample += play_note(t, tick, &voices[v]);
		}

		if (dump){
			int output = sample*32767;
			putchar(output);
			putchar(output >> 8);
			putchar(output);
			putchar(output >> 8);
		}
		channel_l[t] = sample;
		channel_r[t] = sample;

		timer -= BEAT_DELTA;
	}

	return ret;
}
