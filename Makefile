tarbombgame : main.o Tarbomb.o
	g++ -std=c++11 main.o Tarbomb.o -lncurses -o tarbombgame

main.o : main.cpp Tarbomb.cpp Tarbomb.h
	g++ -Wall -std=c++11 -c main.cpp -lncurses

Tarbomb.o : Tarbomb.cpp Tarbomb.h
	g++ -Wall -std=c++11 -c Tarbomb.cpp -lncurses

clean :
	rm *.o tarbombgame