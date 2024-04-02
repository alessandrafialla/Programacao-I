# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -g # flags de compilacao
CC = gcc

all: main.o racionais.o
	$(CC) -o main main.o racionais.o

racionais.o: racionais.c
	$(CC) -c $(CFLAGS) racionais.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f *.o *~ main
