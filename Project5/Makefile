CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -W -Werror -pedantic

minQ: minpriority.o graph.o sspapp.o
	$(CXX) -o minQ minpriority.o graph.o sspapp.o
	
minpriority.o: minpriority.cpp minpriority.h

graph.o: graph.cpp graph.h

sspapp.o: sspapp.cpp sspapp.h

clean:
	rm -f *.o minQ