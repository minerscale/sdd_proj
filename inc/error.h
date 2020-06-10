#ifndef ERROR_H
#define ERROR_H

/*
Error codes:

0: Successful
1: 'General Error'
2: 'Could not open file for reading'
3: 'Invalid .wav file'
*/

void throw(char *msg, int code);

#endif // ERROR_H
