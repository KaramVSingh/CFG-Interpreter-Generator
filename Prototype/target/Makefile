CC = gcc
CFLAGS = -g -Wall -O0 -Werror -Wshadow -Wwrite-strings

core: core.o tokenize.o
	$(CC) -o core core.o tokenize.o

core.o: core.c tokenize.h
	$(CC) $(CFLAGS) -c core.c

tokenize.o: tokenize.c tokenize.h
	$(CC) $(CFLAGS) -c tokenize.c

clean:
		rm -f *.o core
