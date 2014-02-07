all:
	g++ -c busRoute.cpp
	g++ -c main.cpp
	g++ -o pa1 busRoute.o main.o
	./pa1
clean:
	rm *.o pa1
