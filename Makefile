# Makefile for megaint

COMPILER="g++"

objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

foo : $(objects)
	$(COMPILER) -o main $(objects)

clean:
	rm -f *.o main
