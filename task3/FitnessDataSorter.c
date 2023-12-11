#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Declare the global filename variable
char filename[256];

// Function to tokenize a record
void tokeniseRecord(char* record, char delimiter, char* date, char* time, int* steps) {
    char* ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}

// Comparator function for qsort
int compareFitnessData(const void* a, const void* b) {
    FitnessData* data1 = (FitnessData*)a;
    FitnessData* data2 = (FitnessData*)b;
    return data2->steps - data1->steps; // For descending order
}

// Main function
int main() {
    printf("Enter Filename: ");
    scanf("%255s", filename); // Read the filename from user

    // Open the file for reading
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", filename);
        return 1;
    }

    // Read the data into an array of FitnessData
    FitnessData data[1000]; // Assuming we won't have more than 1000 records
    int count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        tokeniseRecord(buffer, ',', data[count].date, data[count].time, &data[count].steps);
        count++;
    }
    fclose(file);

    // Sort the array
    qsort(data, count, sizeof(FitnessData), compareFitnessData);

    // Change the file extension to .tsv
    char* dot = strrchr(filename, '.');
    if (dot) {
        strcpy(dot, ".csv.tsv");
    }
    else {
        strcat(filename, ".csv.tsv");
    }

    // Open the file for writing
    file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", filename);
        return 1;
    }

    // Write the sorted data to the file
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\t%s\t%d\n", data[i].date, data[i].time, data[i].steps);
    }

    fclose(file);

    printf("Data sorted and written to %s\n", filename);
    return 0;
}
