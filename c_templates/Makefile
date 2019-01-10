CC = gcc
CFLAGS = -g -Wall

all: main clean

main: main.o tokenize.o
	$(CC) -o main main.o tokenize.o

main.o: main.c tokenize.h
	$(CC) $(CFLAGS) -c main.c

tokenize.o: tokenize.c tokenize.h
	$(CC) $(CFLAGS) -c tokenize.c

clean:
	rm -f *.o
