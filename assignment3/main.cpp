#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <bitset>
using namespace std;

class hash_entry{
private:
	char* key;
	int start_index;
	int end_index;
public:
	hash_entry(const char* v_key, int v_start_index, int v_end_index);
	char* getkey() const;
	int getstart_index() const;
	int getend_index() const;
};

hash_entry::hash_entry(const char* v_key, int v_start_index, int v_end_index){
	start_index = v_start_index;
	end_index = v_end_index;
	key = new char[v_end_index-v_start_index+2];
	for(int i=v_start_index; i <= v_end_index; i++){
		*(key+i-v_start_index) = *(v_key+i);
	}
	*(key+v_end_index+1) = '\0';
}
char* hash_entry::getkey() const{
	return key;
}
int hash_entry::getstart_index() const{
	return start_index;
}
int hash_entry::getend_index() const{
	return end_index;
}

int code_integer_casting(const char* s);
int code_component_sum(const char* s);
int code_polynomial_sum(const char* s);
int code_cyclic_sum(const char* s);

int value_division(int code, int m);
int value_mad(int code, int a, int b, int m);
int value_multiplication(int code, int m);

int main(){
	string s="abcdefghijk";
	int a = code_polynomial_sum(s.c_str());
	cout<<(a)<<endl;
	cout<<value_division(a,111)<<endl;
	cout<<value_mad(a,2,5,111)<<endl;
	cout<<value_multiplication(a,111)<<endl;

	hash_entry h(s.c_str(), 0, s.size()-1);
	char* p = h.getkey();
	string t(p);
	cout<<t<<endl;
	int b = code_polynomial_sum(t.c_str());
	cout<<(b)<<endl;
	cout<<value_division(b,111)<<endl;
	cout<<value_mad(b,2,5,111)<<endl;
	cout<<value_multiplication(b,111)<<endl;
	
	return 0;
}

int code_integer_casting(const char* s){
	int code = 0;
	int n;
	for(n=0;s+n != NULL && *(s+n) != '\0';n++) {}
	for(int i=0; i<4 && i<n; i++){
		code += (*(s+n-i-1))<<(8*i);
	}
	return code;
}
int code_component_sum(const char* s){
	int code = 0;
	int n;
	for(n=0;s+n != NULL && *(s+n) != '\0';n++) {}
	for(int i=0; i<n; i++){
		code += *(s+i);
	}
	return code;
}
int code_polynomial_sum(const char* s){
	int code = 0;
	int a = 33;
	int n;
	for(n=0;s+n != NULL && *(s+n) != '\0';n++) {}
	for(int i=0; i<n; i++){
		code = a*code + *(s+i);
	}
	return code;
}
int code_cyclic_sum(const char* s){
	int code = 0;
	int h = 5;
	int n;
	for(n=0;s+n != NULL && *(s+n) != '\0';n++) {}
	for(int i=0; i<n; i++){
		code = (code<<h)+ (code>>(32-h));
		code += *(s+i);
	}
	return code;
}

int value_division(int code, int m){
	code = (code >= 0)? code : (-1)*code;
	return (code%m);
}
int value_mad(int code, int a, int b, int m){
	code = (code >= 0)? code : (-1)*code;
	a = a%m;
	b = b%m;
	return ((a*(code%m)%m)+b)%m;
}
int value_multiplication(int code, int m){
	code = (code >= 0)? code : (-1)*code;
	double a = 1.61803398875;
	double temp = a*((double)code);
	double intpart;
	double fracpart = modf(temp,&intpart);
	double ans = ((double)m)*fracpart;
	ans = floor(ans);
	return (int)ans;
}
