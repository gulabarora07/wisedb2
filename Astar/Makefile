CC = g++
CC_FLAGS = -std=c++11
COMPILE = $(CC) $(CC_FLAGS)

all: a.out

a.out: main.o graph.o dijkstra.o vertex.o
	$(COMPILE) -o $@ main.o graph.o dijkstra.o vertex.o

vertex.o: vertex.h query.h
	$(COMPILE) -c vertex.cpp

graph.o: graph.cpp vertex.h query.h
	$(COMPILE) -c graph.cpp

dijkstra.o: dijkstra.cpp graph.h vertex.h query.h
	$(COMPILE) -c dijkstra.cpp

main.o: main.cpp vertex.h query.h graph.h
	$(COMPILE) -c main.cpp

clean:
	rm a.out *.o

run:
	./a.out