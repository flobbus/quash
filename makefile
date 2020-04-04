quash: main.o 
	g++ -g -Wall main.o -o quash 

main.o: main.cpp
	g++ -g -Wall -c main.cpp

clean:
	rm quash 
