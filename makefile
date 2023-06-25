SHELL = /bin/bash
CC = gcc
CFLAGS = -g -Wall -O3

SRC := floodit.c graph.c queue.c main.c
objs = $(SRC:.c=.o)
EXE = floodit

.PHONY: all clean purge

all: $(EXE)

$(EXE): $(objs)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(objs)

purge:
	rm -f $(objs) $(EXE)