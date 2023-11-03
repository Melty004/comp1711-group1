#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100 // 

typedef struct {
    char date[11];
    char time[6];
    int steps;
} FITNESS_DATA;

int main() {
    char filename[50];
    printf("请输入要读取的文件名：");
    scanf("%s", filename);

    // 
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("无法打开文件。\n");
        return -1;
    }

    // 
    int count = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        count++;
    }
    rewind(fp); // 

    // 
    printf("记录总数：%d\n", count);

    // 
    int num;
    printf("请输入要读取的行数：");
    scanf("%d", &num);
    num = (num > count) ? count : num;

    // 
    FITNESS_DATA data;
    for (int i = 0; i < num; i++) {
        fgets(line, MAX_LINE_LENGTH, fp);
        sscanf(line, "%[^,],%[^,],%d", data.date, data.time, &data.steps);
        if (i == num - 1) {
            printf("%s/%s/%d\n", data.date, data.time, data.steps);
        }
    }

    // 
    fclose(fp);

    return 0;
}

