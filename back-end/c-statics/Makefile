CC = gcc
CFLAGS = -g -Wall

main: main.o lexer.o parser.o
	$(CC) -o main main.o lexer.o parser.o

main.o: main.c lexer.h
	$(CC) $(CFLAGS) -c main.c

lexer.o: lexer.c lexer.h
	$(CC) $(CFLAGS) -c lexer.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

clean:
	rm -f *.o