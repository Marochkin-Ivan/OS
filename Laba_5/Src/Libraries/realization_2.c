#include <math.h>
#include <stdio.h>
#include "library.h"

float SinIntegral(float A, float B, float e) {
    printf("In 2-nd realization\n");
    int n = (B - A) / e;
    float s = 0;

    for (int i = 0; i < n - 1; ++i){
        s += 2*(sinf(A + i*e));
    }

    s *= (B - A) / (2*n);
    return s;
}

int PrimeCount(int A, int B){
    printf("In 2-nd realization\n");
    int res = 0;
    int matrix[B];

    for (int i = 0; i < B; ++i){
        matrix[i] = i;
    }
    matrix[1] = 0;

    for (int i = 2; i < B; ++i){
        if (matrix[i] != 0){
            if (matrix[i] >= A){
                res += 1;
            }
            for (int j = 2*i; j < B; j += i){
                matrix[j] = 0;
            }
        }
    }
    return res;
}
