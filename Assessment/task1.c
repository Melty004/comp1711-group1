#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
                    char *date, char *time, char *steps) {
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
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}

// Function to read data from a file and print specific records
void readAndPrintData(const char *filename, int lineNumber) {
    // Open the CSV file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件。\n");
        return;
    }

    // Define an array of FITNESS_DATA to store records
    FITNESS_DATA records[1000]; // Assume not more than 1000 records

    int recordCount = 0; // Initialize record count

    // Read and process each line in the file
    char line[100]; // Assume each line is not longer than 100 characters
    while (fgets(line, sizeof(line), file) != NULL) {
        // Tokenize the line to extract date, time, and steps
        char date[11], time[6], steps[20];
        tokeniseRecord(line, ",", date, time, steps);

        // Convert steps to an integer
        int stepCount = atoi(steps);

        // Store the data in the records array
        strcpy(records[recordCount].date, date);
        strcpy(records[recordCount].time, time);
        records[recordCount].steps = stepCount;

        recordCount++; // Increment the record count
    }

    // Close the file
    fclose(file);

        // Print the total record count
    printf("记录总数：%d\n", recordCount);

    // Print the specified line in the specified format
    if (lineNumber >= 1 && lineNumber <= recordCount) {
        printf("%s/%s/%d\n", records[lineNumber - 1].date, records[lineNumber - 1].time, records[lineNumber - 1].steps);
    } else {
        printf("无效的行数。\n");
    }
}

int main() {
    // Ask the user for the file name to read
    char filename[100];
    printf("请输入要读取的数据文件名：");
    scanf("%s", filename);

    // Read and print data from the specified file
    int lineNumber;
    printf("请输入要打印的行数：");
    scanf("%d", &lineNumber);

    // Read and print data from the specified file
    readAndPrintData(filename, lineNumber);

    return 0;
}