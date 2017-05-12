CC = g++
override CFLAGS += -std=c++11

all: main 
	$(CC) $(CFLAGS) main.o decoder.o instruction_procedures.o int24.o -o sicEmu

main: decoder
	$(CC) $(CFLAGS) -c src/main.cpp -o main.o

decoder: instruction_procedures
	$(CC) $(CFLAGS) -c src/decoder.cpp -o decoder.o

instruction_procedures: int24
	$(CC) $(CFLAGS) -c src/instruction_procedures.cpp -o instruction_procedures.o

int24:
	$(CC) $(CFLAGS) -c src/int24.cpp -o int24.cpp -o int24.o

clean:
	rm *.o a.out
