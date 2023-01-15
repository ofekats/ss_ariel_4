CC = gcc
FLAG = -Wall -g

all: graph

graph.o:graph.c
	$(CC) $(FLAG) -c graph.c

graph: graph.o
	$(CC) $(FLAG) graph.o -o graph

.PHONY: all clean


clean: 
	rm -f *.o graph