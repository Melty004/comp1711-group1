#ifndef FITNESS_DATA_STRUCT_H
#define FITNESS_DATA_STRUCT_H

#include <stdio.h>

// Define an appropriate struct
typedef struct {
	char date[11]; // date
	char time[6]; // time
	int steps; // steps
} FITNESS_DATA;

// Helper function prototypes
void tokeniseRecord(const char* input, const char* delimiter, char* date, char* time, char* steps);

#endif // FITNESS_DATA_STRUCT_H