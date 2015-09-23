#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>
#include "index.h"

using namespace std;

class Node{
	int page, father;// if father == -1  node is root
	//vector<unsigned long> keys;
 	vector<int> sons;
 	vector<Index> keys;
	public:
	Node();
	//void setKeys(vector <unsigned long>);
	//vector <unsigned long> getKeys();
	void setKeys(vector <Index>);
	vector <Index> getKeys();
	void setPage(int);
	int getPage();
	void setFather(int);
	int getFather();
	void setSons(vector<int>);
	vector<int> getSons();
	string toString();
};

#endif
