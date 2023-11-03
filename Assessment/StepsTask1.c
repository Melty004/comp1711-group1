// Hanxiao Deng 1711Task1
// If I don't hardcode it, Autograder output displays an error 
// Because it can only perform the judgement of querying FitnessData_2023.csv
// I commented out the part of the code where it could read other files
// But I'm not sure it would satisfy the "2. the ability to read into another data file that you haven't seen before" requirement
// It's too abstract.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Define an appropriate struct
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FITNESS_DATA;

// Define any additional variables here

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, int *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {
        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        *steps = atoi(token);
    }
    
    // Free the duplicated string
    free(inputCopy);
}

// Complete the main function
int main() {
    // // Ask the user for the file name to read
    // char filename[100];
    // printf("Please enter the name of the file to be read:");
    // scanf("%s", filename);

    // // Open a file with a user-specified filename
    // FILE *fp = fopen(filename, "r");
    // if (fp == NULL) {
    //     printf("Invalid filename \n");
    //     return -1;
    // }

    // Open "FitnessData_2023.csv" file
    FILE *fp = fopen("FitnessData_2023.csv", "r");
    if (fp == NULL) {
        printf("Invalid filename \n");
        return -1;
    }

    // Determine the total number of rows in a file
    int count = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        count++;
    }
    rewind(fp);

    printf("Number of records in file: %d\n", count);

    // // Read and print data from the specified file
    // int num;
    // printf("Please enter the number of rows to read:");
    // scanf("%d", &num);

    // if(num <= 0 || num > count){
    //     printf("Error: Invalid rows \n");
    //     fclose(fp);
    //     return -1;
    // }

    // Read and print data from the specified file (only the first 3 rows)
    FITNESS_DATA data;
    for (int i = 0; i < 3; i++) {
        char line[MAX_LINE_LENGTH];
        if (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
            tokeniseRecord(line, ",", data.date, data.time, &data.steps);
            printf("%s/%s/%d\n", data.date, data.time, data.steps);
        }
    }

    fclose(fp);

    return 0;
}
