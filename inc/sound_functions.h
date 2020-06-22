#ifndef SOUND_FUNCTIONS_H
#define SOUND_FUNCTIONS_H

void sort_audio(int num_samples, float *data);
void square_root(int num_samples, float *data);

void (*function_table[2])(int, float *);

#endif // SOUND_FUNCTIONS_H
