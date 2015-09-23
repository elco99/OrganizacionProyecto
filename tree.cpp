#include "tree.h"
#include "index.h"
#include <iostream>
#include <iterator>

using namespace std;
/*
	ULTIMAS MODIFICACIONES
		* el split y el promote funcionaron con el arbol de prueba, aun no es recursivo 
		* supuestamente ya esta! falta poner los hijos durante el split/promote
		* funcion de agregar funcional, recursiva; hijos,padres y pages correctos y considerado caso de la raiz
*/
Tree::Tree(int orden){
	this->orden = orden;
	root = -1;
}
Tree::~Tree(){
	for (int i = 0; i < arbol.size(); ++i)
	{
		delete arbol[i];
	}
}
void Tree::setRoot(int root){
	this->root = root;
}
int Tree::Tree::getRoot(){
	return root;
}
int Tree::BinarySearch(vector<Index> vector,unsigned long key){
	int mid;
	int low = 0;
	int high = vector.size() -1;

	while(low <= high){
		mid = (low + high)/2;
		//cout << mid;
		if(key == vector.at(mid).getKeys()){
			return mid;
		}else{
			if(key < vector.at(mid).getKeys()){
				if(mid != 0){// evitamos que se salga del vector
					if(key > vector.at(mid - 1 ).getKeys()){// comprobamos la posicion adyacente
						return mid;
					}else{// reducimos el tamanio de nuestra busqueda
						high = mid-1;
					}
				}else{// caso que sea menor que el primer elemento se insertara al inicio
					return mid;
				}
			}else{
				if(mid != vector.size() -1){// evitamos que se salga del vector
					if(key < vector.at(mid+1).getKeys()){// comprobaos la posicion adyacente
						return mid+1;
					}else{
						low = mid +1;
					}
				}else{//caso que sea mayor que el ultimo elemento solo se le hara append
					return -1;
				}

			}
		}
	}


	return  -1;// el retorno de -1 significa que no se encontro la llave o que debe insertarse al final, el segundo solo aplicara a casos de insercion.
}
int Tree::EliminarBinarySearch(vector<Index> vector,unsigned long key){
	int mid;
	int low = 0;
	int high = vector.size() -1;

	while(low <= high){
		mid = (low + high)/2;
		//cout << mid;
		if(key == vector.at(mid).getKeys()){
			return mid;
		}else{
			if(key < vector.at(mid).getKeys()){
				if(mid != 0){// evitamos que se salga del vector
					if(key > vector.at(mid - 1 ).getKeys()){// comprobamos la posicion adyacente
						return -1;
					}else{// reducimos el tamanio de nuestra busqueda
						high = mid-1;
					}
				}else{// caso que sea menor que el primer elemento se insertara al inicio
					return -1;
				}
			}else{
				if(mid != vector.size() -1){// evitamos que se salga del vector
					if(key < vector.at(mid+1).getKeys()){// comprobaos la posicion adyacente
						return -1;
					}else{
						low = mid +1;
					}
				}else{//caso que sea mayor que el ultimo elemento solo se le hara append
					return -1;
				}

			}
		}
	}
	return  -1;// el retorno de -1 significa que no se encontro la llave o que debe insertarse al final, el segundo solo aplicara a casos de insercion.
}
void Tree::Listar(){
	for (int i = 0; i < arbol.size(); i++){
		if (arbol.at(i)->getFather() != -5)
		{
			cout<< arbol.at(i)->toString()<<endl;		
		}
			
	}
	cout << "----------------------------------------"<<endl;
}
