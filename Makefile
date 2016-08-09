CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++14

EXE=mazer

SRC=$(wildcard *.cpp) $(wildcard */*.cpp)
DEPENDENCIES=$(SRC:.cpp=.o)

all: $(DEPENDENCIES)
	$(CC) $(CFLAGS) $^ -o $(EXE)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f *.o */*.o $(EXE)

