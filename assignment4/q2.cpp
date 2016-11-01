#include <iostream>
#include <fstream>
#include <string>

#include "Avl.h"
using namespace std;


int main(){

    

    cout<<"Question 2"<<endl;
	typedef Entry<int,string> Entry;
	AVL<Entry> tree;

    ifstream input;
    input.open("input2.txt");

    int key;
    string value;
    while(input>>key>>value){
        tree.put(key, value);
    }


    cout<<endl<<"-----------------Resulting Tree---------------------"<<endl;
    tree.print();
    cout<<"----------------------------------------------------"<<endl<<endl;

    int sum;
    cout<<"Enter the target sum to search for: ";
    cin>>sum;
    tree.targetsum(sum);
	
	input.close();

	return 0;
}
