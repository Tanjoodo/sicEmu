CC = g++
override CFLAGS += -std=c++11

all: main int24 instruction_procedures decoder
	$(CC) $(CFLAGS) main.o decoder.o instruction_procedures.o int24.o -o sicEmu

main: 
	$(CC) $(CFLAGS) -c src/main.cpp -o main.o

decoder: 
	$(CC) $(CFLAGS) -c src/decoder.cpp -o decoder.o

instruction_procedures: 
	$(CC) $(CFLAGS) -c src/instruction_procedures.cpp -o instruction_procedures.o

int24:
	$(CC) $(CFLAGS) -c src/int24.cpp -o int24.cpp -o int24.o

clean:
	rm *.o sicEmu
