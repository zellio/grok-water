
CC = gcc -O3 -x c -std=c99
RM = rm -Rf

CFLAGS = -c -Wall -Wextra -Werror -pedantic-errors -Wdouble-promotion -Wformat=2 -Winit-self -Wmissing-include-dirs -Wparentheses -Wswitch-default -Wswitch-enum -Wsync-nand -Wuninitialized -Wunknown-pragmas -Wstrict-overflow=2 -Wfloat-equal -Wundef -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wconversion -Wlogical-op -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wmissing-format-attribute -Wpacked -Wpacked-bitfield-compat -Wpadded -Wdouble-promotion -Wformat=2 -Winit-self -Wmissing-include-dirs -Wparentheses -Wswitch-default -Wswitch-enum -Wsync-nand -Wuninitialized -Wunknown-pragmas -Wstrict-overflow=2 -Wfloat-equal -Wundef -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wconversion -Wlogical-op -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wmissing-format-attribute -Wpacked -Wpacked-bitfield-compat -Wpadded -Wredundant-decls -Wnested-externs -Winline -Woverlength-strings -Wcomments -Wundef -Wunused-macros -Wendif-labels
LDFLAGS =

SRCROOT = src/core
INCROOT = src/header
TSTROOT = src/test

OBJROOT = build

VPATH=$(SRCROOT):$(INCROOT):$(TSTROOT):$(OBJROOT)

.PHONY: all

all:

fast.o: math/fast.c math/fast.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

vector.o: math/vector.c math/vector.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

matrix.o: math/matrix.c math/matrix.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

inspect.o: math/inspect.c math/inspect.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

math: fast.o vector.o matrix.o inspect.o

simulation.o: simulation.c simulation.h math
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

.PHONY: clean

clean:
	$(RM) $(OBJROOT)/*.o

.PHONY: rebuild

rebuild: clean math simulation.o
