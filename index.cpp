#include "index.h"
#include <iostream>
#include <string>

using namespace std;

Index::Index(unsigned long keys){
	this-> keys = keys;
}
Index::Index(unsigned long keys,int TreeRRN){
	this->keys = keys;
	this-> TreeRRN = TreeRRN;
}
void Index::setKeys(unsigned long keys){
	this-> keys = keys;
}
unsigned long Index::getKeys(){
	return keys;
}
void Index::setTreeRRN(int TreeRRN){
	this->TreeRRN = TreeRRN;
}
int Index::getTreeRRN(){
	return TreeRRN;
}