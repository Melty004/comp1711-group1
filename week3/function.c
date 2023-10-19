// #include <stdio.h>
// functtion1.c
// int sum (int a, int b)
// {
//     int answer;
//     answer = a + b;
//     return answer;
// }

// int main () 
// {
//     int y = 2;
//     int z = sum(5, y); // calling our new function

//     printf ("The sum of 5 and %d is %d\n", y, z);
// }

// #include <stdio.h>
//function2.c
// float sum (int a, int b)
// {
//     int answer;
//     answer = a + b;
//     return answer;
// }

// int main () 
// {
//     int y = 2;
//     float z = sum(5, y); // calling our new function

//     printf ("The sum of 5 and %d is %f\n", y, z);
// }


// #include <stdio.h>
//function4:
// float fahr_to_celsius (float f_temp)
// {
//     float c_temp;
//     c_temp = (f_temp - 32)/1.8;
//     return c_temp;
// }

// float fahr_to_kelvin (float f_temp)
// {
//     float k_temp;
//     k_temp = fahr_to_celsius(f_temp) + 273.15;
//     return k_temp;
// }

// int main () 
// {
//     float fahrenheit;
//     char option;

//     printf ("Enter a temperature to convert in Fahrenheit:\n");
//     scanf ("%f", &fahrenheit);

//     printf ("\n");
//     printf ("Select A to convert to Celsius\n");
//     printf ("Select B to convert to Kelvin\n");
//     printf ("Select Q to quit\n");

//     scanf(" %c", &option);

//     switch (option)
//     {
//         case 'A': printf ("Converted to degrees Celsius: %f\n", fahr_to_celsius(fahrenheit));
//                   break;

//         case 'B': printf ("Converted to Kelvin: %f\n", fahr_to_kelvin(fahrenheit));
//                   break;

//         case 'Q': break;

//         default:  break;
//     }

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//strsplit.c:
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
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

int main() {
    char record[21] = "2023-09-01,07:30,300";
    char date[11];
    char time[6];
    char steps[10];  // Large enough to hold a typical step count as a string

    int stepsint;
    
    tokeniseRecord(record, ",", date, time, steps);
    
    printf("Date: %s\n", date);
    printf("Time: %s\n", time);
    printf("Steps: %s\n", steps);

    // Convert the steps string to an integer
    stepsint = atoi(steps);
    printf("Steps as an integer: %d\n", stepsint);
    
    return 0;
}