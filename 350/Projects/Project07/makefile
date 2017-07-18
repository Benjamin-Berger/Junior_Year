all: test1.o test2.o
	g++ -o v1 test1.o
	g++ -o v2 test2.o

test1.o: test1.cpp
	g++ -c test1.cpp

test2.o: test2.cpp
	g++ -c test2.cpp

clean:
	rm-f *.o v1 v2
