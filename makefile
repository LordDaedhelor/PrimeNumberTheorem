all: find

clean:
	rm *.o

find: main.cpp
	g++ -g --std=c++11 -o find main.cpp

run:
	./find

val:
	valgrind ./find