#include <iostream>
#include "Avl.h"
using namespace std;

int main(){
	AVL<Entry<int,int> > a;
	a.root = a.insert(a.root, 9, 1);
    a.root = a.insert(a.root, 5,2);
    a.root = a.insert(a.root, 10,3);
    a.root = a.insert(a.root, 0,4);
    a.root = a.insert(a.root, 6,5);
    a.root = a.insert(a.root, 11,6);
    a.root = a.insert(a.root, -1,7);
    a.root = a.insert(a.root, 1,8);
    a.root = a.insert(a.root, 2,9);
	a.print(a.root);
	a.root = a.remove(a.root, 10);
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<"New"<<endl<<endl;
	a.print(a.root);
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<"Search"<<endl<<endl;
	a.print(a.search(a.root, 9));

	return 0;
}