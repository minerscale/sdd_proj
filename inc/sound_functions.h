#ifndef SOUND_FUNCTIONS_H
#define SOUND_FUNCTIONS_H

#define SAMPLE_RATE 44100.0
#define NUM_SECONDS 24
#define NUM_SAMPLES (int)(SAMPLE_RATE*NUM_SECONDS)

float **process(int num_samples, int dump);

#endif // SOUND_FUNCTIONS_H
