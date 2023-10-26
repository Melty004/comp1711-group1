#include <stdio.h>
#include <string.h>

typedef struct {
    char name [20];
    char student_id [11]; // Assuming 10 digits.
    unsigned mark;
} student;
typedef unsigned long long int array_size_t;
int main () {
    // Data generated using ChatGPT.
    int number_of_students = 10, i;
    student students [] = {
        {"Alice Smith",    "64827593", 67},
        {"Bob Johnson",    "19374650", 89},
        {"Charlie Brown",  "82056914", 76},
        {"David Davis",    "45790182", 44},
        {"Eve Wilson",     "36102478", 91},
        {"Frank Anderson", "93571826", 53},
        {"Grace Lee",      "50249867", 78},
        {"Hannah Clark",   "74820591", 62},
        {"Isaac Harris",   "61093745", 89},
        {"Jack White",     "92847501", 72},
    };
        array_size_t array_size = 256; // 64-bit integers
    char array [array_size];
    for (array_size_t i = 0; i < array_size-1; i++)
        array[i]  = i + 1;
    array[array_size - 1] = '\0';

    printf("The string is %s character long: %ld\n", array, strlen(array));
    printf("-------------\n");
    return 0;}