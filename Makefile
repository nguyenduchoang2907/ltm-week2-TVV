CFLAGS = -c -Wall
CC = gcc

all: resolver

resolver: hww2.o
	${CC} hww2.o -o resolver

hww2.o: hww2.c
	${CC} ${CFLAGS} hww2.c

clean:
	rm -f *.o *~ resolver