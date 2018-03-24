CC = g++
CC_FLAGS = -std=c++14
COMPILE = $(CC) $(CC_FLAGS)

all: a.out

a.out: main.o vertex.o graph.o dijkstra.o astar.o
	$(COMPILE) -o $@ main.o graph.o dijkstra.o vertex.o astar.o

vertex.o: vertex.h query.h
	$(COMPILE) -c vertex.cpp

graph.o: graph.cpp vertex.h query.h
	$(COMPILE) -c graph.cpp

dijkstra.o: dijkstra.cpp graph.h vertex.h query.h algos.h
	$(COMPILE) -c dijkstra.cpp

astar.o: astar.cpp graph.h vertex.h query.h algos.h
	$(COMPILE) -c astar.cpp	

main.o: main.cpp vertex.h query.h graph.h
	$(COMPILE) -c main.cpp

clean:
	rm a.out *.o

run:
	./a.out