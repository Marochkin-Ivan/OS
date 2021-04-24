#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "library.h"

float SinIntegral(float A, float B, float e) {
    printf("In 1-st realization\n");
    int n = (B - A) / e;
    float s = 0;

    for (int i = 0; i < n - 1; ++i){
        s += sinf(A + i*e);
    }

    s *= e;
    return s;
}

int PrimeCount(int A, int B) {
    printf("In 1-st realization\n");
    int res = 0;
    bool prime = true;

    if (A == 1 || A == 2){
        res = 1;
        A = 3;
    }

    for (int i = A; i <= B; ++i){
        for (int j = 2; j < i - 1; ++j){
            if (i % j == 0){
                prime = false;
                break;
            }
        }
        if (prime == true){
            res += 1;
        }
        prime = true;  
    }
    return res;
}
