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
void Tree::Eliminar(Index key){
	int cont = 0;
	if(key.getKeys() == -2){
		for (int i = 0; i < arbol.size(); ++i){
			cout<< arbol.at(i)->toString()<<endl;	
		}
		cout << "----------------------------------------"<<endl;
		return;
	}
	if(root != -1){
		Node * currentNode = arbol.at(cont);
		int posicion = EliminarBinarySearch(currentNode->getKeys(), key.getKeys());
		while (posicion == -1){//Recorrer arbol hasta localizar clave
			currentNode = arbol.at(cont);
			posicion = EliminarBinarySearch(currentNode->getKeys(), key.getKeys());
			if(posicion != -1){
				break;
			}
			cont++;
		}
		if(posicion == -1)
			return;
		vector<Index> keys = currentNode->getKeys();
		if(currentNode->getSons().size() == 0){//Si key esta en la hoja eliminar
			keys.erase(keys.begin() + posicion);
			currentNode->setKeys(keys);
		}else{//si key no es hoja, se intercambia con su sucesor inmediato
			// nos movemos hasta su sucesor inmediato, el cual es la hoja menor de su hijo mayor
			int posicionNodoOriginalAEliminar = currentNode->getPage();
			Index tempKey = currentNode->getKeys().at(posicion);
			currentNode = arbol.at(currentNode->getSons().at(posicion+1));

			while(true){//nos movemos hasta el nodo donde deberia ir la clave (hasta la hoja)	
				if(currentNode->getSons().size() != 0 ){
					currentNode = arbol.at(currentNode->getSons().at(0));		
				}else
					break;
			}
			// cambiamos la llave con el menor de su hijo mayor
			keys.insert(keys.begin() + posicion, currentNode->getKeys().at(0) );
			keys.erase(keys.begin() + posicion+1);			
			arbol.at(posicionNodoOriginalAEliminar)->setKeys(keys);
			keys = currentNode->getKeys();
			//keys.insert(keys.begin() +0 ,  tempKey);
			keys.erase(keys.begin() + 0);
			currentNode->setKeys(keys);

		}
		Underflow(currentNode);

	}
}

void Tree::Underflow(Node* currentNode){
	int minimoDeClavesAceptadas = ((orden+1)/2)-1 ;
	if(currentNode->getKeys().size() < minimoDeClavesAceptadas){// se verifica que esta en underflow
		//CASO DE REDISTRIBUCION
		int page = currentNode->getPage();
		int father = currentNode->getFather() ;
		currentNode = arbol.at(father);
		int posicion = -1;
		for (int i = 0; i < currentNode->getSons().size(); ++i)	{
			if(currentNode->getSons().at(i) == page){
				posicion = i;
				break;
			}
		}
		bool entro = false;
		if(posicion != 0){
			if(arbol.at(currentNode->getSons().at(posicion-1))->getKeys().size() > minimoDeClavesAceptadas ){//si le puede prestar el hermano izquierdo
				// se verifica este primero por convecion
				vector<Index> keys = arbol.at(page)->getKeys();
				keys.insert(keys.begin()+0, currentNode->getKeys().at(posicion-1));
				arbol.at(page)->setKeys(keys);// inserta la llave del padre en el nodo con underflow

				keys =  currentNode->getKeys();
				keys.insert(keys.begin() + posicion-1, arbol.at(currentNode->getSons().at(posicion-1))->getKeys().at(arbol.at(currentNode->getSons().at(posicion-1))->getKeys().size()-1)  );
				keys.erase(keys.begin() + posicion); 
				currentNode->setKeys(keys);
				keys =  arbol.at(currentNode->getSons().at(posicion-1))->getKeys() ;
				keys.pop_back();
				arbol.at(currentNode->getSons().at(posicion-1))->setKeys(keys); 
				vector<int> sons = arbol.at(currentNode->getSons().at(posicion))->getSons();
				if(arbol.at(currentNode->getSons().at(posicion-1))->getSons().size() != 0){
					sons.push_back(arbol.at(currentNode->getSons().at(posicion-1))->getSons().at(arbol.at(currentNode->getSons().at(posicion-1))->getSons().size()-1));
				}
				arbol.at(currentNode->getSons().at(posicion))->setSons(sons);
				sons = arbol.at(currentNode->getSons().at(posicion-1))->getSons();
				if(arbol.at(currentNode->getSons().at(posicion-1))->getSons().size() != 0){
					sons.pop_back();
				}
				arbol.at(currentNode->getSons().at(posicion-1))->setSons(sons);
				Underflow(arbol.at(currentNode->getSons().at(posicion-1)));
				return;
			}

		}
		if(currentNode->getKeys().size() > posicion){// si el nodo en underflow tiene hermano derecho
			if(arbol.at(currentNode->getSons().at(posicion+1))->getKeys().size() > minimoDeClavesAceptadas){
				//se verifica el hermano derecho			
				vector<Index> keys = arbol.at(page)->getKeys();
				keys.push_back(currentNode->getKeys().at(posicion));
				arbol.at(page)->setKeys(keys);
				keys =  currentNode->getKeys();
				keys.insert(keys.begin() + posicion, arbol.at(currentNode->getSons().at(posicion+1))->getKeys().at(0));			
				keys.erase(keys.begin() + posicion+1);
				currentNode->setKeys(keys);
				keys =  arbol.at(currentNode->getSons().at(posicion+1))->getKeys() ;
				keys.erase(keys.begin()+0);
				arbol.at(currentNode->getSons().at(posicion+1))->setKeys(keys); 
				vector<int> sons = arbol.at(currentNode->getSons().at(posicion))->getSons();
				if(arbol.at(currentNode->getSons().at(posicion+1))->getSons().size() != 0){
					sons.push_back(arbol.at(currentNode->getSons().at(posicion+1))->getSons().at(0));
				}
				arbol.at(currentNode->getSons().at(posicion))->setSons(sons);
				sons = arbol.at(currentNode->getSons().at(posicion+1))->getSons();
				if(arbol.at(currentNode->getSons().at(posicion+1))->getSons().size() != 0){
					sons.erase(sons.begin()+0);
				}
				arbol.at(currentNode->getSons().at(posicion+1))->setSons(sons);
				Underflow(arbol.at(currentNode->getSons().at(posicion+1)));

				return;
			}
		}
		//FIN REDISTRIBUCION
		//CASO CONCATENACION
		// en este punto esta garantizado que sus hermanos no tienen para prestar
		entro = false;
		if(posicion != 0){// si no es el primero
			int hermano = currentNode->getSons().at(posicion-1);
			vector<Index> keys = arbol.at(hermano)->getKeys();
			keys.push_back(currentNode->getKeys().at(posicion-1));//se inserta el padre primero ya que es menor que los hijos que se insertaran del nodo en underflow
			for (int i = 0; i < arbol.at(currentNode->getSons().at(posicion))->getKeys().size(); ++i){// se aniaden todos los valores del nodo en underflow a el nodo de su izquierda (siempre el de la izquierda)

				keys.push_back(arbol.at(currentNode->getSons().at(posicion))->getKeys().at(i));
			}			
			arbol.at(hermano)->setKeys(keys);// -
			vector<int> sons = arbol.at(hermano)->getSons();
			for (int i = 0; i < arbol.at(currentNode->getSons().at(posicion))->getSons().size(); ++i){// se aniaden todos los valores del nodo en underflow a el nodo de su izquierda (siempre el de la izquierda)

				sons.push_back(arbol.at(currentNode->getSons().at(posicion))->getSons().at(i));
			}
			//cout << currentNode->toString()<< "----------"<<endl;;
			if(currentNode->getSons().size() !=0){
				for (int i = 0; i < arbol.at(currentNode->getSons().at(posicion))->getSons().size(); ++i){// se ocupa la posicion del hermano del currentNode
					arbol.at(arbol.at(currentNode->getSons().at(posicion))->getSons().at(i))->setFather(currentNode->getSons().at(posicion-1));
				}
				//arbol.at(currentNode->getSons().at(posicion-1))->setFather(arbol.at(hermano)->getPage());
			}
			arbol.at(hermano)->setSons(sons);
			keys = currentNode->getKeys();
			keys.erase(keys.begin() + posicion-1);//se borra el padre ya que fue insertado y se correran el resto de valores
			currentNode->setKeys(keys);
			sons  = currentNode->getSons();
			sons.erase(sons.begin() + posicion);//se borra la referencia al hijo que se unio, en este caso el que quedo en underflow,
			// ya que fue insertado y se correran el resto de valores
			currentNode->setSons(sons);
			// luego tenemos que comprobar si el padre y el nodo hermano que fue afectado no termino en underflow.
			if(currentNode->getPage() != root){
				Underflow(currentNode);
			}else{
				if(currentNode->getKeys().size() == 0){
					root = currentNode->getSons().at(0);
					arbol.at(currentNode->getSons().at(0))->setFather(-1);
					currentNode->setFather(-5);// para indicar que el nodo fue borrado
				}

			}
			arbol.at( page) ->setFather(-5);// para indicar que el nodo fue borrado
			
		}else if(posicion == 0){
			int hermano = currentNode->getSons().at(posicion+1);
			int NodoEnUnderflow = currentNode->getSons().at(posicion);
			vector<Index> keys = arbol.at(NodoEnUnderflow)->getKeys();
			keys.push_back(currentNode->getKeys().at(posicion));//se inserta el padre primero ya que es menor que los hijos que se insertaran al nodo en underflow
			for (int i = 0; i < arbol.at(hermano)->getKeys().size(); i++){// se aniaden todos los valores del hermano a el nodo en underflow 

				keys.push_back(arbol.at(hermano)->getKeys().at(i));
			}			
			arbol.at(NodoEnUnderflow)->setKeys(keys);// -
			vector<int> sons = arbol.at(NodoEnUnderflow)->getSons();
			for (int i = 0; i < arbol.at(hermano)->getSons().size(); ++i){// se aniaden todos los hijos del hermano a el nodo en underflow 
				sons.push_back(arbol.at(hermano)->getSons().at(i));
			}
			if(currentNode->getSons().size() !=0){//no es hoja
				for (int i = 0; i < arbol.at(hermano)->getSons().size(); ++i){// se ocupa la posicion del hermano del currentNode
					
					arbol.at(arbol.at(NodoEnUnderflow)->getSons().at(i))->setFather(hermano);
				}
			}
			arbol.at(NodoEnUnderflow)->setSons(sons);
			keys = currentNode->getKeys();
			keys.erase(keys.begin() + posicion);//se borra el padre ya que fue insertado y se correran el resto de valores
			currentNode->setKeys(keys);
			sons  = currentNode->getSons();
			sons.erase(sons.begin() + (posicion+1));//se borra la referencia al hijo que se unio, en este caso el hermano
			// ya que fue insertado y se correran el resto de valores
			currentNode->setSons(sons);
			// luego tenemos que comprobar si el padre y el nodo hermano que fue afectado no termino en underflow.
			
			if(currentNode->getPage() != root){//recursiva para underflow
				Underflow(currentNode);
			}else{
				if(currentNode->getKeys().size() == 0){
					root = currentNode->getSons().at(0);
					arbol.at(currentNode->getSons().at(0))->setFather(-1);
					currentNode->setFather(-5);// para indicar que el nodo fue borrado
				}

			}
			arbol.at( hermano) ->setFather(-5);// para indicar que el nodo fue borrado
		}
	}//fin de verificacion de underflow

}
int Tree::PaginaSucesorInmediato(Node* currentNode,int posicion){
	currentNode = arbol.at(currentNode->getSons().at(posicion+1));
	while(true){//nos memos hasta el nodo donde deberia ir la clave (hasta la hoja)	
		if(currentNode->getSons().size() != 0 ){
			currentNode = arbol.at(currentNode->getSons().at(0));		
		}else
			return currentNode->getPage();
	}
}
int Tree::PaginaPredecesorInmediato(Node* currentNode,int posicion){
	currentNode = arbol.at(currentNode->getSons().at(posicion-1));
	while(true){//nos movemos hasta el nodo donde deberia ir la clave (hasta la hoja)	
		if(currentNode->getSons().size() != 0 ){
			currentNode = arbol.at(currentNode->getSons().at(currentNode->getKeys().size()-1));		
		}else
			return currentNode->getPage();
	}
}
