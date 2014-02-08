all:
	g++ -c busRoute.cpp
	g++ -c main.cpp
	g++ -o pa1 busRoute.o main.o
	./pa1
	rm *.o pa1
clean:
	rm *.o pa1
test:
	g++ -c busRoute.cpp
	g++ -c unitTest.cpp
	g++ -o pa1Test busRoute.o unitTest.o
	./pa1Test	