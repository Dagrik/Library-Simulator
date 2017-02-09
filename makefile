PROGS := lib

all: $(PROGS)


lib: Book.o Patron.o Library.o Menu.o
	g++ -g Book.o Patron.o Library.o Menu.o -o lib

Book.o: Book.cpp Book.hpp
	g++ -c Book.cpp

Patron.o: Patron.cpp Patron.hpp
	g++ -c Patron.cpp

Library.o: Library.cpp Library.hpp
	g++ -c Library.cpp

Menu.o: Menu.cpp
	g++ -c Menu.cpp


clean:
	rm -f $(PROGS) *.o *~
