#include <iostream>

using namespace std;

int factorial(int n){
    if(n!=1){
	return(n * factorial(n-1));
    }
    else return 1;
}


int main(){
   cout<< "Hello IIT Ropar" << endl;
    cout << endl;
    cout << "The factorial of 5 is " << factorial(5) << endl;
    cout<< " enter two numbers";
    int a, b;
	cin>>  a >> b ;
    cout << "Sum is : " << a+b << endl;

 return 0;
}
