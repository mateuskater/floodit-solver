SHELL = /bin/bash
CC = gcc
CFLAGS = -g -Wall -O3

# ---------------------------------------

subdir = queue-graph/src
sources := $(shell $\
             gfl=$$(ls {g,q}*.c); $\
             echo "$$gfl")
sources += $(wildcard *.c)
objects = $(sources:.c=.o)
exec = floodit

# ---------------------------------------

.PHONY: all clean purge

# ---------------------------------------

all: $(exec)

$(exec): $(objects)
	$(CC) $(CFLAGS) $^ -o $@

# ---------------------------------------

clean:
	rm -f $(objects)

purge:
	rm -f $(objects) $(exec)


# EXE = solve
# SRC = main.c

# all: $(EXE)

# $(EXE): $(SRC)
# 	gcc $(SRC) -o $(EXE) -g

# clean:
# 	rm -f $(EXE)
# 	rm *.o