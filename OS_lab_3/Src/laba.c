#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// Глобальные переменные:
long long bulls_eye = 0; // сумма попаданий в область окружности во всех потоках
pthread_mutex_t mutex;

// структура данных для потоковой функции:
typedef struct {
    long long tries_count; 
    int rad;
    long long circle_points; 
    long long idx;
} pthread_Data;

// потоковая функция:
void* ThreadFunction(void* thread_data){
    srand(time(NULL));
    pthread_Data* data = (pthread_Data*) thread_data;
//    printf("Running thread number %d. Count of tries = %lld Wait...\n", data->idx + 1, data->tries_count);
    double x, y;
    for (long long i = 0; i < data->tries_count; ++i){
        x = (double)rand() / (double)RAND_MAX * (2*data->rad) - data->rad;
        y = (double)rand() / (double)RAND_MAX * (2*data->rad) - data->rad;
        if ((x*x + y*y) <= data->rad*data->rad){
            ++data->circle_points;
        }
    }
    pthread_mutex_lock(&mutex);
    bulls_eye += data->circle_points;
    pthread_mutex_unlock(&mutex); 
    return NULL;
}

int main(int argc, char* argv[]){

    if (argc != 3){
        perror("ERROR: invalid count of arguments");
        exit(-1);
    }

    long long thr_count = atoll(argv[1]);
    if (thr_count < 1){
        perror("ERROR: invalid first argument");
        exit(-2);
    }

    long long all_tries = atoll(argv[2]);
    if (all_tries < 1){
        perror("ERROR: invalid second argument");
        exit(-3);
    }

    printf("Enter radius: ");
    int rad;
    scanf("%d", &rad);
    if (rad < 1){
        perror("ERROR: invalid radius");
        exit(-4);
    }

    // выделяем память для массивов идентификаторов потоков и структур данных потоков:
    pthread_t* thread_id = (pthread_t*) malloc(thr_count * sizeof(pthread_t));
    pthread_Data* threadData = (pthread_Data*) malloc(thr_count * sizeof(pthread_Data));
    pthread_mutex_init(&mutex, NULL);

    clock_t begin_time = clock(); // запускаем таймер работы программы

    // присваиваем нужные значения данным и запускаем потоки:
    for (long long i = 0; i < thr_count; ++i){
        threadData[i].rad = rad;
        threadData[i].idx = i;
        threadData[i].circle_points = 0;
        if (i == thr_count - 1){
            threadData[i].tries_count = all_tries/thr_count + all_tries%thr_count;
        }
        else{
            threadData[i].tries_count = all_tries/thr_count;
        }
        pthread_create(&thread_id[i], NULL, ThreadFunction, &threadData[i]);
    }

    // ждем завершения всех потоков:
    for (long long i = 0; i < thr_count; ++i){
        pthread_join(thread_id[i], NULL);
    }

    clock_t end_time = clock(); // останавливаем таймер работы программы

    printf("S = %f\n", bulls_eye/((double)all_tries) * 2*rad * 2*rad); // выводим результат

    free(thread_id);
    free(threadData);
    pthread_mutex_destroy(&mutex);
    
    printf("Program running time = %f\n\n",
           (double)(end_time - begin_time) / CLOCKS_PER_SEC);
    return 0;
}
