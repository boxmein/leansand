# Leansand makefile

LFLAGS=-mwindows -LSDL2/lib -lmingw32 -lSDL2main -lSDL2 -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid
CFLAGS=-Iinclude -ISDL2/include -Wall

CC=gcc
FILES=src/leansand.cpp

# .PHONY: all debug release test
# all: debug test

debug: $(patsubst src/%.cpp, build/%.o, $(FILES))
	$(CC) -o build/leansand-debug $(LFLAGS) $^

# release: $(FILES:.cpp=.o)
#   $(CC) -o build/leansand-debug $(LFLAGS) $^

# test:
#   echo Not Yet Implemented

build/%.o: src/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
