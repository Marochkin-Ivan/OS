CC = g++

all: program_A program_B program_C

program_A: program_A.cpp
	$(CC) $^ -o A

program_B: program_B.cpp
	$(CC) $^ -o B

program_C: program_C.cpp
	$(CC) $^ -o C

clean:
	rm -rf *.o A B C