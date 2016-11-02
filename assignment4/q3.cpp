#include <iostream>
#include <string>

#include "RB.h"

using namespace std;

void menu();

int main(){
	cout<<"Question 3"<<endl;
	typedef Entry<int,string> Entry;
	rbtree<Entry> tree;

	menu();
    int input;
    int k;
    string v;
    cin>>input;
    rbtree<Entry>::Iterator i (tree.end());

    while(input){
        cout<<endl;
        switch(input){

            case 1:
           	cout<<"Enter key : ";
            cin>>k;
            cout<<"Enter value : ";
            cin>>v;
            cout<<endl;
            i = tree.insert(k,v);
            break;

            case 3:
            cout<<
        }
        cout<<endl<<"-----------------Resulting Tree---------------------"<<endl;
        tree.print();
        cout<<"----------------------------------------------------"<<endl<<endl;
        menu();
        cin>>input;
    }
	
	return 0;
}

void menu(){
    cout<<endl;
    cout<<"Enter your choice"<<endl;
    cout<<"1. insert(k,v)"<<endl;
    cout<<"2. remove(k)"<<endl;
    cout<<"3. remove(p) p is last iterator"<<endl;
    cout<<"4. search(k)"<<endl;
    cout<<"5. leafcount()"<<endl;
    cout<<"6. height()"<<endl;
    cout<<"7. blackheight()"<<endl;
    cout<<"8. keyinrange(a,b)"<<endl;
    cout<<"9. empty()"<<endl;
    cout<<"10. size()"<<endl;
    cout<<"0. Exit"<<endl;

}