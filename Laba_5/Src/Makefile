CC = gcc
CFLAGS = -pedantic -Wall
CLIBFLAGS = -fPIC -shared

all: program_1_rel_1 program_1_rel_2 program_2

# program_1

program_1_rel_1: program_1.o realization_1.o
	$(CC) $(CFLAGS) $^ -o $@
	
program_1_rel_2: program_1.o realization_2.o
	$(CC) $(CFLAGS) $^ -o $@
	
program_1.o: ./Programs/program_1.c
	$(CC) $(CFLAGS) -c $^

realization_1.o: ./Libraries/realization_1.c ./Libraries/library.h
	$(CC) $(CFLAGS) $< -c

realization_2.o: ./Libraries/realization_2.c ./Libraries/library.h
	$(CC) $(CFLAGS) $< -c

#program 2

program_2: program_2.o realization_1.so realization_2.so
	$(CC) $(CFLAGS) $< -o $@ 
	
program_2.o: ./Programs/program_2.c
	$(CC) $(CFLAGS) -c $^

realization_1.so: ./Libraries/realization_1.c ./Libraries/library.h
	$(CC) $(CFLAGS) $(CLIBFLAGS) $< -o $@

realization_2.so: ./Libraries/realization_2.c ./Libraries/library.h
	$(CC) $(CFLAGS) $(CLIBFLAGS) $< -o $@

clean:
	rm -rf program_1_rel_1 program_1_rel_2 program_2 *.o *.so