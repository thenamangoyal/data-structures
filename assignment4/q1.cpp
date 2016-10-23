#include <iostream>
#include "Avl.h"
using namespace std;

int main(){
	AVL<Entry<int,int> > a;
	//AVL<Entry<int,int> >::Iterator i = a.insert(3,5);
	a.insert(8,9);
	a.insert(2,5);
	a.insert(3,4);
	a.print(a.root);


	return 0;
}