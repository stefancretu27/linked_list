CC = g++
DBG_FLAGS = -g -Wall
CFLAGS = -std=c++11

all:
	$(CC) $(CFLAGS) $(DBG_FLAGS) list.cpp main.cpp -o list

valgrind:
	valgrind --tool=memcheck ./list

clean:
	rm list;