#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <sys/mman.h>

typedef struct {
    uint8_t check;
    double result;
} Data;

// создание временного файла:
int get_tmpFile(void){
    char* tmpFileName = strdup("/tmp/OS_laba4_tmpFile.XXXXXX");
    if (tmpFileName == NULL){
        perror("strdup failed");
        exit(-7);
    }
    int fd = mkstemp(tmpFileName);
    if (fd == -1){
        perror("mfstemp failed");
        exit(-8);
    }
    if (unlink(tmpFileName) == -1){
        perror("unlink failed");
        exit(-9);
    }
    free(tmpFileName);
    write(fd, "\0\0\0\0\0\0\0\0\0\0", 10);
    return fd;
}

// запись:
void write_in_mmapFile(Data* data, void* mmapFile){
    uint8_t* check = (uint8_t*)mmapFile;
    double* result = (double*)(mmapFile + sizeof(uint8_t));

    *check = data->check;
    *result = data->result;
}

// чтение:
void read_from_mmapFile(Data* data, void* mmapFile){
    uint8_t* check = (uint8_t*)mmapFile;
    double* result = (double*)(mmapFile + sizeof(uint8_t));

    data->check = *check;
    data->result = *result;
}

int main(){
 
    printf("Enter file name: ");

    // считываем имя файла:
    char file_name[256];
    gets(file_name);

    // открываем файл с введенным именем: 
    int commands = open(file_name, O_RDONLY);
    if (commands == -1){
        perror("Can't open file");
        exit(-2);
    }

    // создаем и мапим временный файл:
    int fd_tmpFile = get_tmpFile();
    void* mmapFile = mmap(/*start*/ NULL,/*length*/ 10,/*prot*/ PROT_READ | PROT_WRITE,/*flags*/ MAP_SHARED,/*fd*/ fd_tmpFile,/*offset*/ 0);
    if (mmapFile == MAP_FAILED){
        perror("mmap failed");
        exit(-6);
    }

    // создаем дочерний процесс:
    int id = fork();

    if (id == -1){
        perror("fork error");
        exit(-3);
    }
    else if (id == 0){

        double num[50];
        Data data;
        data.check = 1;

        dup2(commands, 0); // перенаправляем стандартный поток ввода дочернего процесса на открытый файл

        // считываем 3 числа типа double из файла:
        int i = 0;
        while(scanf("%lf", &num[i]) != EOF){
            ++i;
        }
        
        printf("Count of numbers = %d\n", i);
        // делаем проверку деления на 0:
        for (int j = 1; j < i; ++j){
            if (num[j] == 0){
                perror("Can't divide");
                data.check = 0;
                write_in_mmapFile(&data, mmapFile); // если возможно деление на 0, отправляем данные родительскому процессу и завершаем работу
                exit(-5);
            }
        }

        // считаем и отправляем данные родительскому процессу:
        data.result = num[0];
        for (int j = 1; j < i; ++j){
            data.result /= num[j];
        }
        write_in_mmapFile(&data, mmapFile);
    }
    else {
        Data data;
    
        wait(&id); // ждем завершения работы дочернего процесса

        // считываем данные от дочернего процесса:
        read_from_mmapFile(&data, mmapFile);
        if (data.check == 0) 
            exit(-5); // завершаем работу, если в дочернем процессе было деление на 0
            
        printf("Result from child = %lf\n", data.result);
    }
    
    close(fd_tmpFile);
    close(commands);
    return 0;
}