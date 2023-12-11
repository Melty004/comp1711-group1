// 预处理指令，用于禁用特定编译器警告
#define _CRT_SECURE_NO_WARNINGS

// 包含标准输入输出库、标准库和字符串库的头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义用于存储健康数据的结构体
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// 函数用于将记录分词
void tokeniseRecord(char* record, char delimiter, char* date, char* time, int* steps) {
    // 使用strtok函数将记录按照指定分隔符进行分词
    char* ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        // 将分词结果复制到对应的变量中
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                // 将步数转换为整数并存储
                *steps = atoi(ptr);
            }
        }
    }
}

// 用于qsort排序的比较函数
int compareFitnessData(const void* a, const void* b) {
    FitnessData* data1 = (FitnessData*)a;
    FitnessData* data2 = (FitnessData*)b;
    // 按照步数降序排序
    return data2->steps - data1->steps;
}

// 主函数
int main() {
    // 存储文件名的字符数组
    char filename[256];
    printf("Enter Filename: ");
    scanf("%255s", filename); // 从用户输入中读取文件名

    // 打开文件以供读取
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", filename);
        return 1;
    }

    // 读取数据并存储到FitnessData数组中
    FitnessData data[1000]; // 假设不会有超过1000条记录
    int count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        // 调用tokeniseRecord函数将读取的每一行数据进行分词
        tokeniseRecord(buffer, ',', data[count].date, data[count].time, &data[count].steps);
        count++;
    }
    fclose(file);

    // 对数组进行排序
    qsort(data, count, sizeof(FitnessData), compareFitnessData);

    // 将文件扩展名更改为.tsv
    char* dot = strrchr(filename, '.');
    if (dot) {
        strcpy(dot, ".csv.tsv");
    }
    else {
        strcat(filename, ".csv.tsv");
    }

    // 打开文件以供写入
    file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", filename);
        return 1;
    }

    // 将排序后的数据写入文件
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\t%s\t%d\n", data[i].date, data[i].time, data[i].steps);
    }

    fclose(file);

    printf("Data sorted and written to %s\n", filename);
    return 0;
}
