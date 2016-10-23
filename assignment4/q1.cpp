#include <iostream>
#include "Avl.h"
using namespace std;

int main(){
	typedef Entry<int,int> Entry;
	AVL<Entry> a;
	
	a.put(9, 1);
    a.put(5,2);
    a.put(10,3);
    a.put(0,4);
    a.put(6,5);
    a.put(11,6);
    a.put(-1,7);
    a.put(1,8);
    a.put(2,9);
    a.put(2,5);
   	cout<<"Final tree"<<endl;
	a.print();
	
	

	return 0;
}