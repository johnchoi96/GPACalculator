CC = gcc
CFLAGS = -Wall -g

gpa: gpa.o data.o calculate.o print.o file.o
gpa.o: gpa.c data.h print.h
data.o: data.c data.h
calculate.o: data.h calculate.h calculate.c
print.o: print.c print.h
file.o: file.c file.h data.h

clean:
	rm -rf *.o
	rm -rf *.gch
