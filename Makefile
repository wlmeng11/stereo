CC=g++
LIBS=opencv
FLAGS=-c -Wall -O2 --std=c++11 $(shell pkg-config $(LIBS) --cflags)
#CCFLAGS=-c -Wall -O2
LDFLAGS=$(shell pkg-config $(LIBS) --libs)
SOURCES=main.cpp argument_processing.cpp client.c server.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

clean:
	$(shell rm -rf *o $(EXECUTABLE) )

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(FLAGS) $< -o $@
