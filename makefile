#Paths
VPATH=./build ./include ./src
# Object paths
OBJECTS=*.o
OPATH=./build

# Headers
HEADERS=./include/*.h
HPATH=./include

all: main.o 
	g++ -o ejecutable -I ./build ./build/point.o -I ./build ./build/pelfin.o -I ./build ./build/dato.o -I ./build ./build/main.o 
	mv ejecutable ./bin/ejecutable
main.o: header.h point.h pelfin.h dato.h mesh.h point.cpp pelfin.cpp dato.cpp  main.cpp 
	g++ -c -I $(HPATH) $(wildcard HEADERS)  -I ./src ./src/point.cpp 
	g++ -c -I $(HPATH) $(wildcard HEADERS)  -I ./Eigen -I  ./src ./src/pelfin.cpp 
	g++ -c -I $(HPATH) $(wildcard HEADERS)  -I ./src ./src/dato.cpp 
	g++ -c -I $(HPATH) $(wildcard HEADERS)  -I ./Eigen/ -I ./src ./src/main.cpp 
	mv point.o ./build/point.o
	mv pelfin.o ./build/pelfin.o
	mv dato.o ./build/dato.o
	mv main.o ./build/main.o	
