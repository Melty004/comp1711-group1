#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
char filename[256];         // Define a string variable filename to store the filename, with a length of 256
FITNESS_DATA* data = NULL;  // Define a pointer variable data to the FITNESS_DATA structure and initialise it to NULL
int dataCount = 0;          // Define an integer variable dataCount to record the number of data, initialised to 0

int loadFile();
void displayTotalRecords();
void findFewestSteps();
void findLargestSteps();
void findMeanStepCount();
void findLongestContinuousPeriod();

void tokeniseRecord(const char* input, const char* delimiter,
    char* date, char* time, char* steps) {
    // Creates a copy of the input string, since the strtok function modifies the original string
    char* inputCopy = strdup(input);

    // Split the copy string using the specified separator
    char* token = strtok(inputCopy, delimiter);
    if (token != NULL) {
        strcpy(date, token);  // Copy the first result into the date character array
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);  // Copy the result of the second word segmentation into the time character array
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);  // Copy the third result into the steps character array
    }

    // Free the copied string memory
    free(inputCopy);
}
int loadFile(const char *filename) 
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {  // If the file is not found or fails to open, an error message is output and returned
        printf("Error: Could not find or open the file.\n");
        return 1;
    }

    // Count the number of records in the file
    char buffer[1024];
    while (fgets(buffer, 1024, file)) {  // Loop through each line of data in the file
        dataCount++;  // For each line read, the number of data is increased by one
    }
    // Allocate memory for the data array
    data = (FITNESS_DATA*)malloc(sizeof(FITNESS_DATA) * dataCount);     // Dynamically allocates memory space based on the amount of data, 
    // which is the size of the FITNESS_DATA structure multiplied by the amount of data

    // Move pointer back to beginning of file
    fseek(file, 0, SEEK_SET);   //fseek(file, 0, SEEK_SET);  // Relocate the file pointer to the beginning of the file in order to re-read the file data

    // Read data from file line by line
    // Re-reading and parsing the data
    int i = 0;
    while (fgets(buffer, 1024, file)) { 
        char date[11];
        char time[6];
        char steps[5];  
        tokeniseRecord(buffer, ",", date, time, steps);  // Parses the rows of data and saves the result in the corresponding character array
        strcpy(data[i].date, date);     // Copy the date into the data array
        strcpy(data[i].time, time);     // Copy the time into the data array
        data[i].steps = atoi(steps);    // Converts the number of steps to an integer and saves it in the data array
        i++;                            // Continue processing the next line of data
    }

    fclose(file);  // Close file handle
    return 0;
}
// Display the total number of records in the file
void displayTotalRecords() {
    printf("Total records: %d\n", dataCount); //// Total records of output data
}

// Find the date and time of the timeslot with the fewest steps
void findFewestSteps() {
    int minSteps = data[0].steps;  // Initialise the minimum number of steps to the first piece of data
    int index = 0;  // Initialise index to 0
    for (int i = 1; i < dataCount; i++) {  // Iterating over data arrays
        if (data[i].steps < minSteps) { 
            minSteps = data[i].steps;  // Update minimum steps
            index = i;  // Update index
        }
    }

    printf("Fewest steps: %s %s\n", data[index].date, data[index].time);  // Output the date and time corresponding to the minimum number of steps
}


// Find the date and time of the timeslot with the largest number of steps
void findLargestSteps() {
    int maxSteps = data[0].steps;  // Initialise the maximum number of steps for the first piece of data
    int index = 0;  // Initialise index to 0
    for (int i = 1; i < dataCount; i++) {  // Iterating over data arrays
        if (data[i].steps > maxSteps) { 
            maxSteps = data[i].steps;  // Update maximum steps
            index = i;  // Update index
        }
    }

    printf("Largest steps: %s %s\n", data[index].date, data[index].time);  // Output the date and time corresponding to the maximum number of steps
}


// Find the mean step count of all the records in the file
void findMeanStepCount() {
    int totalSteps = 0;  // Initialise step sum to 0
    for (int i = 0; i < dataCount; i++) {  // Iterate over data arrays
        totalSteps += data[i].steps;  // Accumulate the number of steps per data
    }

    float meanStepCount = totalSteps / (float)dataCount;  // Calculate the average number of steps (need to convert the total number of steps to floating point)
    printf("Mean step count: %.0f\n", meanStepCount);  // Output the average number of steps (keep the integer part)
}


// Find the longest continuous period where the step count is above 500 steps
void findLongestContinuousPeriod() {
    int currentLength = 0;  // Initialise the number of days where the current number of consecutive steps is greater than 500 to 0
    int maxLength = 0;  // Initialise the number of days where the longest continuous step is greater than 500 to 0
    int startIndex = 0;  // Initialise the starting index of the days with the longest consecutive steps greater than 500 to 0
    int endIndex = 0;  //  Initialise the end index of the days where the longest consecutive step is greater than 500 to 0
    for (int i = 0; i < dataCount; i++) {  // Iterate over data arrays
        if (data[i].steps > 500) {  // If the number of steps in the current data is greater than 500
            currentLength++;  // Add 1 to the number of days that the current number of steps in a row is greater than 500
            if (currentLength > maxLength) {  // If the current number of consecutive days with a step count greater than 500 exceeds the maximum number of consecutive steps
                maxLength = currentLength;  //  Update the maximum number of consecutive steps
                endIndex = i;  // Update the end index of the longest consecutive step
                startIndex = endIndex - maxLength + 1;  // Update the starting index of the longest consecutive steps
            }
        }
        else {  // If the number of steps in the current data is not greater than 500
            currentLength = 0;  // The number of days with a current continuous step count greater than 500 is zeroed out
        }
    }

    printf("Longest period start: %s %s\n", data[startIndex].date, data[startIndex].time);  // Output the start date and time of the longest consecutive steps
    printf("Longest period end: %s %s\n", data[endIndex].date, data[endIndex].time);  // Output the end date and time of the longest consecutive step
}


// Complete the main function
int main() {
    char choice;

    while (1) {
        printf("\nMenu Options:\n");
        printf("A: Specify the filename to be imported\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");
        printf("D: Find the date and time of the timeslot with the largest number of steps\n");
        printf("E: Find the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q: Quit\n");
        printf("Enter choice: ");
        scanf(" %c", &choice);

        switch (choice) {
        case 'A':
            printf("Input filename: ");
            scanf("%s", filename);
            if (loadFile(filename) == 1){
                return 1;
            }
            break;
        case 'B':
            displayTotalRecords();
            break;
        case 'C':
            findFewestSteps();
            break;
        case 'D':
            findLargestSteps();
            break;
        case 'E':
            findMeanStepCount();
            break;
        case 'F':
            findLongestContinuousPeriod();
            break;
        case 'Q':
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    }
}