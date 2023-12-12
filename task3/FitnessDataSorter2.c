#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
int tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
                return 1;  // Successful tokenization
            }
        }
    }

    // Handle unexpected input
    printf("Error parsing data. Check the file format.\n");
    return 0;  // Tokenization failed
}

// Function to compare fitness data for sorting
int compareFitnessData(const void *a, const void *b) {
    return ((FitnessData *)b)->steps - ((FitnessData *)a)->steps;
}

int main() {
    char filename[100];
    FILE *file;

    // Step 1: Provide a menu option to specify a filename
    printf("Enter Filename: ");
    scanf("%s", filename);

    // Step 2: Process the data file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file. Check the filename and try again.\n");
        return 1;
    }

    char line[100];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    rewind(file);

    FitnessData *data = malloc(count * sizeof(FitnessData));
    if (data == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (!tokeniseRecord(line, '\t', data[i].date, data[i].time, &data[i].steps)) {
            printf("Error parsing data in line %d: %s\n", i + 1, line);
            fclose(file);
            free(data);
            return 1;
        }
        i++;
    }

    fclose(file);

    // Step 3: Sort the data by descending order of step count
    qsort(data, count, sizeof(FitnessData), compareFitnessData);

    // Step 4: Write out the sorted data file in .tsv format
    char *outputFilename = malloc(strlen(filename) + 5);  // +5 for ".tsv\0"
    if (outputFilename == NULL) {
        printf("Error allocating memory.\n");
        free(data);
        return 1;
    }

    sprintf(outputFilename, "%s.tsv", filename);

    file = fopen(outputFilename, "w");
    if (file == NULL) {
        printf("Error creating output file.\n");
        free(data);
        free(outputFilename);
        return 1;
    }

    for (i = 0; i < count; i++) {
        fprintf(file, "%s\t%s\t%d\n", data[i].date, data[i].time, data[i].steps);
    }

    fclose(file);

    free(data);
    free(outputFilename);

    printf("Sorting and writing successful. Output file: %s\n", outputFilename);

    return 0;
}
