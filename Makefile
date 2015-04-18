# Leansand makefile

LINK=-lSDL -lSDLmain
DEBUGFLAGS=-DDEBUG
CFLAGS=-Iinclude
CC=gcc
FILES=src/leansand.c

.PHONY: all debug release test
all: debug test

debug: $(FILES:.c=.o)
  gcc -o build/leansand-debug $(DEBUGFLAGS) $(CFLAGS) $(LINK)

release: $(FILES:.c=.o)
  gcc -o build/leansand-debug $(RELEASEFLAGS) $(CFLAGS) $(LINK)

test:
  echo Not Yet Implemented

%.o: %.c
  gcc -c $< $(CFLAGS)

