CC = g++

CFLAGS=-c -Wall


all: edit

prim: edit.o
	$(CC) edit.o -o edit

prim.o: edit.cpp
	$(CC) $(CFLAGS) edit.cpp

clean:
	rm -rf *o edit
