tarbombgame : main.o Tarbomb.o
	g++ -std=c++11 main.o Tarbomb.o -lncurses -o tarbombgame

main.o : main.cpp Tarbomb.cpp Tarbomb.h
	g++ -Wall -g -std=c++11 -c main.cpp

Tarbomb.o : Tarbomb.cpp Tarbomb.h
	g++ -Wall -g -std=c++11 -c Tarbomb.cpp

clean :
	rm *.o tarbombgame