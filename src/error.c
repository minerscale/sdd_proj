#include <stdio.h>
#include <stdlib.h>
void throw(char *msg, int code) {
	fprintf(stderr, "Error: %s\n", msg);
	exit(code);
}
