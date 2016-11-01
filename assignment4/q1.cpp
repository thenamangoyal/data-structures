#include <iostream>
#include <string>

#include "Avl.h"
using namespace std;

void menu();

int main(){
    cout<<"Question 1"<<endl;
	typedef Entry<int,string> Entry;
	AVL<Entry> tree;
    menu();
    int input;
    int k;
    string v;
    cin>>input;
    AVL<Entry>::Iterator i (tree.end());

    while(input){
        cout<<endl;
        switch(input){

            case 1:
            i = tree.firstEntry();
            
            if (!(i == tree.end())){
                cout<<"Found entry with key "<<(*i).key()<<" and value "<<(*i).value()<<endl;
            }
            else {
                cout<<"Not found"<<endl;
            }
            break;

            case 2:
            i = tree.lastEntry();
            
            if (!(i == tree.end())){
                cout<<"Found entry with key "<<(*i).key()<<" and value "<<(*i).value()<<endl;
            }
            else {
                cout<<"Not found"<<endl;
            }
            break;

            case 3:
            cout<<"Enter key : ";
            cin>>k;
            i = tree.ceilingEntry(k);
            
            if (!(i == tree.end())){
                cout<<"Found entry with key "<<(*i).key()<<" and value "<<(*i).value()<<endl;
            }
            else {
                cout<<"Not found"<<endl;
            }
            break;

            case 4:
            cout<<"Enter key : ";
            cin>>k;
            i = tree.floorEntry(k);
            
            if (!(i == tree.end())){
                cout<<"Found entry with key "<<(*i).key()<<" and value "<<(*i).value()<<endl;
            }
            else {
                cout<<"Not found"<<endl;
            }
            break;

            case 5:
            cout<<"Enter key : ";
            cin>>k;
            i = tree.lowerEntry(k);
            
            if (!(i == tree.end())){
                cout<<"Found entry with key "<<(*i).key()<<" and value "<<(*i).value()<<endl;
            }
            else {
                cout<<"Not found"<<endl;
            }
            break;

            case 6:
            cout<<"Enter key : ";
            cin>>k;
            i = tree.higherEntry(k);
            
            if (!(i == tree.end())){
                cout<<"Found entry with key "<<(*i).key()<<" and value "<<(*i).value()<<endl;
            }
            else {
                cout<<"Not found"<<endl;
            }
            break;

            case 7:            
            
            cout<<"Size of tree is "<<tree.size()<<endl;
            break;

            case 8:
                      
            if (tree.empty()){
                cout<<"Tree is empty"<<endl;
            }
            else {
                cout<<"Tree is NOT empty"<<endl;
            }
            break;

            case 9:
            cout<<"Enter key : ";
            cin>>k;
            i = tree.find(k);
            
            if (!(i == tree.end())){
                cout<<"Found entry with key "<<(*i).key()<<" and value "<<(*i).value()<<endl;
            }
            else {
                cout<<"Not found"<<endl;
            }
            break;

            case 10:
            cout<<"Enter key : ";
            cin>>k;
            cout<<"Enter value : ";
            cin>>v;
            i = tree.put(k,v);
            
            break;

            case 11:
            cout<<"Enter key : ";
            cin>>k;
            tree.erase(k);
            
            break;

            case 12:
            tree.erase(i);
            
            break;
        }
        cout<<"---------------Tree----------------"<<endl;
        tree.print();
        cout<<"-----------------------------------"<<endl;
        menu();
        cin>>input;
    }
	
	

	return 0;
}

void menu(){
    cout<<endl;
    cout<<"Enter your choice"<<endl;
    cout<<"1. firstEntry()"<<endl;
    cout<<"2. lastEntry()"<<endl;
    cout<<"3. ceilingEntry(k)"<<endl;
    cout<<"4. floorEntry(k)"<<endl;
    cout<<"5. lowerEntry(k)"<<endl;
    cout<<"6. higherEntry(k)"<<endl;
    cout<<"7. size()"<<endl;
    cout<<"8. empty()"<<endl;
    cout<<"9. find(k)"<<endl;
    cout<<"10. put(k,v)​"<<endl;
    cout<<"11. erase(k)"<<endl;
    cout<<"12. erase(p) p is last used iterator"<<endl;
    cout<<"0. Exit"<<endl;

}