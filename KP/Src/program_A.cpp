#include <iostream>
#include <string>
#include <unistd.h>

using std::string;
using std::cin;
using std::cout;

int main (){
    int pipe_A2C[2];
    int pipe_A2B[2];
    int pipe_C2A[2];
    int pipe_C2B[2];

    pipe(pipe_A2C);
    pipe(pipe_A2B);
    pipe(pipe_C2A);
    pipe(pipe_C2B);

    pid_t id_C = fork();
    if (id_C == -1){
        throw std::runtime_error("ERROR: fork error");
    }
    else if (id_C == 0){ // program_C
            char A2C[32];
            char C2A[32];
            char C2B[32];

            sprintf(A2C, "%d", pipe_A2C[0]);
            sprintf(C2A, "%d", pipe_C2A[1]);
            sprintf(C2B, "%d", pipe_C2B[1]);
            
            execl("./C", A2C, C2A, C2B, (char*)(NULL));
    } // program_C end
    else {
        pid_t id_B = fork();
        if (id_B == -1){
            throw std::runtime_error("ERROR: fork error");
        }
        else if (id_B == 0){ // program_B
            char A2B[32];
            char C2B[32];
            sprintf(A2B, "%d", pipe_A2B[0]);
            sprintf(C2B, "%d", pipe_C2B[0]);
            execl("./B", A2B, C2B, (char*)(NULL));
        } // program_B end
        else { // program_A
            string Str;
            while (cin >> Str){
                size_t Sended_char_count = Str.size();
                uint8_t confirm;

                write(pipe_A2B[1], &Sended_char_count, sizeof(size_t));
                write(pipe_A2C[1], &Sended_char_count, sizeof(size_t));
                write(pipe_A2C[1], Str.c_str(), Sended_char_count);

                read(pipe_C2A[0], &confirm, sizeof(uint8_t));
            }
        } // program_A end 
    }
    return 0;
}
