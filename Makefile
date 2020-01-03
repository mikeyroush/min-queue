# makefile

all: Main

Main: QueueMain.cpp MinQueue.h
	g++ -std=c++11 QueueMain.cpp -o Main

clean:
	rm *.o *.gch Main
