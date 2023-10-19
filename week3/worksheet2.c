// #include <stdio.h>
// //Q1: Calculate Area of a Circle
// float circleArea (float a)
// {
//     float area;
//     area = 3.1415 * a;
//     return area;
// }

// int main () 
// {
//     float y = 2;
//     float z = circleArea(y); // calling our new function

//     printf ("The circleArea is %f.\n", z);
// }

#include <stdio.h>
//Q2: Calculate Volume of a Sphere:
float sphere (float a)
{
    int volume;
    volume = (4/3) * 3.14 * a ;
    return volume;
}

int main () 
{
    int y = 2;
    float z = sphere(y); // calling our new function

    printf ("The volume of sphere is %f\n", z);
}