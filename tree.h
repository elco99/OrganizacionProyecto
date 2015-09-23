#ifndef TREE_H
#define TREE_H
#include "node.h"
#include "index.h"
class Tree{
	vector<Node*> arbol;
	int orden;
	int root;
public:
 	Tree(int);
 	~Tree();
	int BinarySearch(vector<Index> ,unsigned long );
	int EliminarBinarySearch(vector<Index> ,unsigned long );
	void Split(int);
	int Promote(int , int );
	void Eliminar(Index);
	void Agregar(Index);
	void setRoot(int);
	int getRoot();
	void Listar();
	int Buscar(unsigned long);
	//void recorrerInorden();
	void Underflow(Node* );
	int PaginaSucesorInmediato(Node* ,int);
	int PaginaPredecesorInmediato(Node* ,int);
};

#endif