quash: main.o 
	g++ -g main.o -o quash 

main.o: main.cpp
	g++ -g -c main.cpp

clean:
	rm *.o  quash 
