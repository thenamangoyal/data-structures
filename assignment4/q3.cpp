#include <iostream>
#include <string>

#include "RB.h"

using namespace std;


int main(){

	typedef Entry<int,int> Entry;
	rbtree<Entry> r;
/*
	cout<<r.getheight()<<" "<<r.getblackheight()<<" "<<r.getcountleaf()<<endl;
	r.print(r.root);*/
	cout<<"New before"<<endl;

	r.insert(10,134234);
	r.insert(20,2435);
	r.insert(30,435);
	r.insert(10,134234);
	r.insert(20,2435);
	r.insert(30,435);
	r.insert(10,134234);
	r.insert(20,2435);
	r.insert(30,435);
	r.insert(15,949);

	r.print_rot();

	r.remove(r.find(10));
	r.remove(r.find(10));
	r.remove(r.find(10));
	r.remove(r.find(10));
	r.remove(10);
	r.remove(10);
	r.remove(10);
	r.print();
	cout<<r.size()<<endl;

	/*r.getkeyinrange(16, 21);
	cout<<"New after"<<endl;

	r.remove(10);
	r.remove(20);
	r.remove(30);
	r.remove(15);

	cout<<r.getheight()<<" "<<r.getblackheight()<<" "<<r.getcountleaf()<<endl;
	r.print(r.root);
	*/
	
	return 0;
}