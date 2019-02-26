CC = gcc
CFLAGS = -g -Wall

all: main clean

main: main.o lexer.o parser.o evaluator.o environment.o
	$(CC) -o main main.o lexer.o parser.o evaluator.o environment.o

main.o: main.c lexer.h
	$(CC) $(CFLAGS) -c main.c

lexer.o: lexer.c lexer.h
	$(CC) $(CFLAGS) -c lexer.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

evaluator.o: evaluator.c evaluator.h environment.h
	$(CC) $(CFLAGS) -c evaluator.c

environment.o: environment.c environment.h
	$(CC) $(CFLAGS) -c environment.c

clean:
	rm -f *.o