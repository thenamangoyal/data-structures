#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>
using namespace std;

unsigned int code_integer_casting (const char* s);
unsigned int code_component_sum (const char* s);
unsigned int code_polynomial_sum (const char* s);
unsigned int code_cyclic_sum (const char* s);

int main(){
	string s = "ad";
	unsigned int a = code_cyclic_sum(s.c_str());
	cout<<(a)<<endl;
	/*reverse(s.begin(),s.end());
	cout<<(*reinterpret_cast<const int*>(s.c_str()))<<endl;*/
	return 0;
}

unsigned int code_integer_casting (const char* s){
	unsigned int code = 0;
	int n;
	for(n=0;s+n != NULL && *(s+n) != '\0';n++) {}
	for(int i=0; i<4 && i<n; i++){
		code += ((unsigned int)(*(s+n-i-1)))<<(8*i);
	}
	return code;
}
unsigned int code_component_sum (const char* s){
	unsigned int code = 0;
	int n;
	for(n=0;s+n != NULL && *(s+n) != '\0';n++) {}
	for(int i=0; i<n; i++){
		code += (unsigned int)(*(s+i));
	}
	return code;
}
unsigned int code_polynomial_sum (const char* s){
	unsigned int code = 0;
	unsigned int a = 33;
	int n;
	for(n=0;s+n != NULL && *(s+n) != '\0';n++) {}
	for(int i=0; i<n; i++){
		code = a*code + (unsigned int)(*(s+i));
	}
	return code;
}
unsigned int code_cyclic_sum (const char* s){
	unsigned int code = 0;
	unsigned int h = 5;
	int n;
	for(n=0;s+n != NULL && *(s+n) != '\0';n++) {}
	for(int i=0; i<n; i++){
		code = (code<<h)+ (code>>(32-h));
		code += (unsigned int)(*(s+i));
	}
	return code;
}