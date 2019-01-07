CC = gcc
CFLAGS = -g

all: core clean

core: core.o tokenize.o parse.o evaluate.o
	$(CC) -o core core.o tokenize.o parse.o evaluate.o

core.o: core.c tokenize.h parse.h
	$(CC) $(CFLAGS) -c core.c

evaluate.o: evaluate.c evaluate.h parse.h tokenize.h
	$(CC) $(CFLAGS) -c evaluate.c

parse.o: parse.c parse.h tokenize.h
	$(CC) $(CFLAGS) -c parse.c

tokenize.o: tokenize.c tokenize.h
	$(CC) $(CFLAGS) -c tokenize.c

clean:
	rm -f *.o
