#include <stdio.h>
#include <errno.h>
#include "error.h"


char *errors[] = {
	"Invalid .wav file."
};

void throw(int error){
	size_t num_msg = sizeof(errors)/sizeof(errors[0]);
	int error_index = -error - 1;

	// Check if the error is custom or not.
	// +ve values for system errors, -ve values for custom errors.
	if ((error_index < num_msg) && (error_index >= 0)){
		fprintf(stderr, "Error: %s\n", errors[error_index]);
	} else {
		// If it is a global error use the builtin error handling.
		errno = error;
		perror("Error");
	}
}
