exe: main.o index.o node.o tree.o
	g++ main.o index.o node.o tree.o -o exe
main.o: main.cpp index.o tree.o
	g++ -c main.cpp
tree.o: tree.cpp tree.h node.h index.h
	g++ -c tree.cpp
node.o: node.cpp node.h index.h
	g++ -c node.cpp
index.o: index.cpp index.h
	g++ -c index.cpp