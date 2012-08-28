
CC = gcc -O3
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Wmissing-prototypes -Wmissing-declarations -c
LDFLAGS =

SRCROOT = ./src/core
INCROOT = ./src/header
TSTROOT = ./src/test

OBJROOT = ./build



.PHONY: all

all:

fast.o:
	$(CC) $(CFLAGS) -I$(INCROOT) $(SRCROOT)/math/fast.c -o $(OBJROOT)/fast.o

vector.o:
	$(CC) $(CFLAGS) -I$(INCROOT) $(SRCROOT)/math/vector.c -o $(OBJROOT)/vector.o

matrix.o:
	$(CC) $(CFLAGS) -I$(INCROOT) $(SRCROOT)/math/matrix.c -o $(OBJROOT)/matrix.o

math: fast.o vector.o matrix.o



.PHONY: clean

clean:
	rm -Rf $(OBJROOT)/*.o
