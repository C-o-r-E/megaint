# Makefile for megaint

#COMPILER=g++ -g
#
#objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
#
#foo : $(objects)
#	$(COMPILER) -o main $(objects)
#
#clean:
#	rm -f *.o main


CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES=main.cpp megaint.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@