#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

void menu (){
	printf("=================================================================\n");
    printf("|| 0 - change realization                                      ||\n");
	printf("|| 1 float float float - count integral sin(x)                 ||\n");
	printf("|| 2 int int - count number of primes                          ||\n");
	printf("|| -1 - Exit                                                   ||\n");
	printf("=================================================================\n");
	printf("\n");
}

int ChangeMode(int realization){
    if (realization == 1){
        return 2;
    }
    else {
        return 1;
    }
}

int main(){
    menu();

	int cmd = -2;
    int realization = 1;
    void* library_handler_1 = NULL;
	void* library_handler_2 = NULL;
	float (*sinintegral)(float, float, float);
    int (*primecount)(int, int);

    if((library_handler_1 = dlopen("realization_1.so", RTLD_LAZY)) == 0){
		printf("Can't open library\n");
		exit(-1);
	}
	if((library_handler_2 = dlopen("realization_2.so", RTLD_LAZY)) == 0){
		printf("Can't open library\n");
		exit(-2);
	}

	while (cmd != -1){
        printf("Enter command: ");
        scanf("%d", &cmd);
        if (cmd == 0){
            printf("Realization was changed from %d to %d\n", realization, ChangeMode(realization));
            realization = ChangeMode(realization);
        }
        else if (cmd == 1){
            float a, b, e;
            if (scanf("%f %f %f", &a, &b, &e) != 3){
                printf("Invalid count of arguments\n");
                menu();
            } else if (realization == 1){
                sinintegral = (float (*)(float, float, float))dlsym(library_handler_1, "SinIntegral");
                printf("integral sin(x) = %f\n", (*sinintegral)(a, b, e));
            }
            else if (realization == 2){
                sinintegral = (float (*)(float, float, float))dlsym(library_handler_2, "SinIntegral");
                printf("integral sin(x) = %f\n", (*sinintegral)(a, b, e));
            }
        }
        else if (cmd == 2){
            int a, b;
            if (scanf("%d %d", &a, &b) != 2) {
                printf("Invalid count of arguments\n");
                menu();
            } else if (realization == 1){
                primecount = (int (*)(int, int))dlsym(library_handler_1, "PrimeCount");
                printf("primes count = %d\n", (*primecount)(a, b));
            }
            else if (realization == 2){
                primecount = (int (*)(int, int))dlsym(library_handler_2, "PrimeCount");
                printf("primes count = %d\n", (*primecount)(a, b));
            }
        }
        else if (cmd == -1){
            break;
        }
        else{
            printf("Unknown command\n");
            menu();
        }
    }
    dlclose(library_handler_1);
	dlclose(library_handler_2);
    return 0;
}
