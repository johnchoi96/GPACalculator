CC = gcc
CFLAGS = -Wall -std=c99 -g

gpa: gpa.o data.o calculate.o print.o
gpa.o: gpa.c data.h print.h
data.o: data.c data.h
calculate.o: data.h calculate.h calculate.c
print.o: print.c print.h

clean:
	rm -rf *.o
	rm -rf *.gch
	rm gpa
	rm gpa.exe
