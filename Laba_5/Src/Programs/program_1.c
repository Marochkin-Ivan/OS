#include <stdio.h>
#include <stdlib.h>
#include "../Libraries/library.h"

void menu (){
	printf("=================================================================\n");
	printf("|| 1 float float float - count integral sin(x)                 ||\n");
	printf("|| 2 int int - count number of primes                          ||\n");
	printf("|| -1 - Exit                                                    ||\n");
	printf("=================================================================\n");
	printf("\n");
}

int main(){
    menu();

	int cmd = 0;
	while (cmd != -1){
        printf("Enter command: ");
        scanf("%d", &cmd);
        if (cmd == 1){
            float a, b, e;
            if (scanf("%f %f %f", &a, &b, &e) != 3){
                printf("Invalid count of arguments\n");
                menu();
            } else {
                printf("integral sin(x) = %f\n", SinIntegral(a, b, e));
            }
            continue;
        }
        else if (cmd == 2){
            int a, b;
            if (scanf("%d %d", &a, &b) != 2) {
                printf("Invalid count of arguments\n");
                menu();
            } else {
                printf("primes count = %d\n", PrimeCount(a, b));
            }
            continue;
        }
        else if (cmd == -1){
            break;
        }
        else{
            printf("Unknown command\n");
            menu();
        }
    }
    return 0;
}
