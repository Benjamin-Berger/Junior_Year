COMPILER = g++
FLAGS = -g -Wall -std=c++0x
EXECUTABLE = submission

all: driver.o
	$(COMPILER) $(FLAGS) -o $(EXECUTABLE) driver.o

Driver.o: driver.cpp
	$(COMPILER) $(FLAGS) -c driver.cpp

clean:
	rm -f *.o $(EXECUTABLE)