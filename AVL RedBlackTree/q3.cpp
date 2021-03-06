#include <iostream>
#include <fstream>
#include <string>

#include "RB.h"

using namespace std;

void menu();

int main(){
	cout<<"Question 3"<<endl;
	typedef Entry<int,string> Entry;
	rbtree<Entry> tree;

	ifstream input;
    input.open("input3.txt");

    int key;
    string value;
    while(input>>key>>value){
        tree.insert(key, value);
    }


    cout<<endl<<"-----------------Resulting Tree---------------------"<<endl;
    tree.print();
    cout<<"----------------------------------------------------"<<endl<<endl;

	menu();
    int choice;
    int k;
    string v;
    cin>>choice;
    rbtree<Entry>::Iterator i (tree.end());
    int a, b;

    while(choice){
        cout<<endl;
        switch(choice){

            case 1:
           	cout<<"Enter key : ";
            cin>>k;
            cout<<"Enter value : ";
            cin>>v;
            cout<<endl;
            i = tree.insert(k,v);
            break;

            case 2:
           	cout<<"Enter key : ";
            cin>>k;
            cout<<endl;
            tree.remove(k);
            break;

            case 3:
            cout<<endl;
            tree.remove(i);
            break;

            case 4:
            cout<<"Enter key : ";
            cin>>k;
            i = tree.find(k);
            cout<<endl;
            if (!(i == tree.end())){
                cout<<"Found entry with key "<<(*i).key()<<" and value "<<(*i).value()<<endl;
            }
            else {
                cout<<"Not found"<<endl;
            }
            break;

            case 5:
            
            cout<<"No of leaf nodes are "<<tree.getcountleaf()<<endl;
            break;

            case 6:
            
            cout<<"Height of tree is "<<tree.getheight()<<endl;
            break;

            case 7:
            
            cout<<"Black Height of tree is "<<tree.getblackheight()<<endl;
            break;

            case 8:
            cout<<"Enter key a: ";
            cin>>a;
            cout<<"Enter key b: ";
            cin>>b;
            cout<<endl<<"Keys in range are"<<endl;
            tree.getkeyinrange(a, b);
            cout<<endl;
            break;

            case 9:
                      
            if (tree.empty()){
                cout<<"Tree is empty"<<endl;
            }
            else {
                cout<<"Tree is NOT empty"<<endl;
            }
            break;

            case 10:
            
            cout<<"Size of tree is "<<tree.size()<<endl;
            break;

            default:
            cout<<endl;
            tree.print_rot();
            break;
        }
        cout<<endl<<"-----------------Resulting Tree---------------------"<<endl;
        tree.print();
        cout<<"----------------------------------------------------"<<endl<<endl;
        menu();
        cin>>choice;
    }
	
	input.close();
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