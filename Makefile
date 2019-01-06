CC = gcc
CFLAGS = -Wall -std=c99 -g

gpa: gpa.o data.o
gpa.o: gpa.c data.c data.h
data.o: data.c data.h

clean:
	rm -rf *.o
