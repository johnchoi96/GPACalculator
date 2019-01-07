CC = gcc
CFLAGS = -Wall -std=c99 -g

gpa: gpa.o data.o calculate.o
gpa.o: gpa.c data.c data.h
data.o: data.c data.h
calculate.o: data.h calculate.h calculate.c

clean:
	rm -rf *.o
