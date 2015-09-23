#ifndef INDEX_H
#define INDEX_H
#include <string>
#include <vector>
using namespace std;
class Index{
	int TreeRRN;
	unsigned long keys;
	public:
	Index(unsigned long);
	Index(unsigned long,int);
	void setKeys(unsigned long);
	unsigned long getKeys();
	void setTreeRRN(int);
	int getTreeRRN();
};

#endif