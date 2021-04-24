#include <iostream>
#include <string>
#include <unistd.h>

int main (int argc, char* argv[]){
    int pipe_A2C = atoi(argv[0]);
    int pipe_C2A = atoi(argv[1]);
    int pipe_C2B = atoi(argv[2]);

    size_t Sended_char_count;

    while (read(pipe_A2C, &Sended_char_count, sizeof(size_t)) > 0){
        char char_str[Sended_char_count];
        read(pipe_A2C, char_str, Sended_char_count);
        std::string Str(char_str, Sended_char_count);
        std::cout << "C: string from program A: " << Str << std::endl;

        size_t Received_char_count = Str.size();
        write(pipe_C2B, &Received_char_count, sizeof(size_t));

        uint8_t confirm = 1;
        write(pipe_C2A, &confirm, sizeof(uint8_t));
    }
}