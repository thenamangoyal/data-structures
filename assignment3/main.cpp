#include <iostream>
#include <fstream>
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
	hash_entry(const hash_entry& h);
	char* getkey() const;
	int getstart_index() const;
	int getend_index() const;
	~hash_entry();
};

class hash_table {
private:
	hash_entry** table;
	int capacity;
	int size;
public:
	hash_table(int v_capacity=0);
	void rehash();
	int getsize() const;
	void insert(const char* v_key, int v_start_index, int v_end_index);
	hash_entry* search(const char* v_key);
	void search_all(const char* v_key);
};

int code_integer_casting(const char* s);
int code_component_sum(const char* s);
int code_polynomial_sum(const char* s);
int code_cyclic_sum(const char* s);

int value_division(int code, int m);
int value_mad(int code, int m, int a, int b);
int value_multiplication(int code, int m);

bool str_equal(const char* a, const char* b);

hash_table::hash_table(int v_capacity){
	size = 0;
	capacity = v_capacity;
	if (capacity>0){
		table = new hash_entry*[capacity];
		for (int i=0; i< capacity; i++){
			table[i] = NULL;
		}
	}
	else {
		table = NULL;
	}

}

int hash_table::getsize() const{
	return size;
}
void hash_table::insert(const char* v_key, int v_start_index, int v_end_index){
	cout<<"Current size: "<<size<<" capacity: "<<capacity<<endl; 
	if (size>=capacity) {
		rehash();
	}

	hash_entry* h = new hash_entry(v_key, v_start_index, v_end_index);
	int code = code_polynomial_sum(h->getkey());
	cout<<"code: "<<code<<" key: "<<h->getkey();
	int value = value_multiplication(code, capacity);
	cout<<" value: "<<value<<endl;
	int i;
	for(i=0; i<capacity; i++){
		if (table[(value+i)%capacity]){
			cout<<"Key present at "<<(value+i)%capacity<<endl;
		}
		else {
			break;
		}
	}
	size++;
	table[(value+i)%capacity] = h;
	cout<<"Inserting key at: "<<(value+i)%capacity<<endl<<endl;	

}

void hash_table::rehash(){
	cout<<"Rehashing"<<endl;
	int new_capacity = (2*capacity > 1)? (2*capacity): 1;
	int new_size = 0;
	hash_entry** new_table = new hash_entry*[new_capacity];
	for (int i=0; i< new_capacity; i++){
		new_table[i] = NULL;
	}

	for (int i =0 ; i< capacity; i++){
		int new_code = code_polynomial_sum(table[i]->getkey());
		int new_value = value_multiplication(new_code, new_capacity);
		int j;
		for(j=0; j<new_capacity; j++){
			if (new_table[(new_value+j)%new_capacity]){
			}
			else {
				break;
			}
		}
		
		new_size++;
		new_table[(new_value+j)%new_capacity] = new hash_entry(*table[i]);
		

	}
	if (table != NULL) {
		for (int i =0 ; i< capacity; i++){
			delete table[i];
		}
		delete [] table;
		cout<<"Deleted old table of size: "<<capacity<<endl; 
	}
	table = new_table;
	capacity = new_capacity;
	size = new_size;
}

hash_entry* hash_table::search(const char* v_key){

	int code = code_polynomial_sum(v_key);
	cout<<"code: "<<code<<" key: "<<v_key;
	int value = value_multiplication(code, capacity);
	cout<<" value: "<<value<<endl;
	for(int i=0; i<capacity; i++){
		if (table[(value+i)%capacity]){
			cout<<"trying string: "<<table[(value+i)%capacity]->getkey()<<" : ";
			char *p = table[(value+i)%capacity]->getkey();
			bool isEqual = str_equal(p,v_key);
			if (isEqual){
				cout<<"Yes"<<endl;
				return table[(value+i)%capacity];
			}
			cout<<"No"<<endl;
		}
		else {
			cout<<"found empty cell"<<endl;
			return NULL;
		}
	}

	cout<<"All cells checked not found"<<endl;
	return NULL;

}

void hash_table::search_all(const char* v_key){
	int code = code_polynomial_sum(v_key);
	cout<<"code: "<<code<<" key: "<<v_key;
	int value = value_multiplication(code, capacity);
	cout<<" value: "<<value<<endl;
	for(int i=0; i<capacity; i++){
		if (table[(value+i)%capacity]){
			cout<<"trying string: "<<table[(value+i)%capacity]->getkey()<<" : ";
			char *p = table[(value+i)%capacity]->getkey();
			bool isEqual = str_equal(p,v_key);
			if (isEqual){
				cout<<"Yes"<<endl;
			}
			else {
				cout<<"No"<<endl;
			}
		}
		else {
			cout<<"found empty cell"<<endl;
			return;			
		}
	}

	cout<<"All cells checked not found"<<endl;

}

hash_entry::hash_entry(const char* v_key, int v_start_index, int v_end_index){
	start_index = v_start_index;
	end_index = v_end_index;
	key = new char[v_end_index-v_start_index+1];
	for(int i=v_start_index; i < v_end_index; i++){
		*(key+i-v_start_index) = *(v_key+i);
	}
	*(key+v_end_index-v_start_index) = '\0';
}

hash_entry::hash_entry(const hash_entry& h){
	start_index = h.start_index;
	end_index = h.end_index;
	key = new char[h.end_index-h.start_index+1];
	for(int i=0; i < h.end_index- h.start_index; i++){
		*(key+i) = *(h.key+i);
	}
	*(key+h.end_index-h.start_index) = '\0';

}

hash_entry::~hash_entry(){
	cout<<"Deleting key: "<<key<<endl;
	delete [] key;
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


int main(){
	hash_table table(64);
	ifstream input;
	input.open("input.txt");
	char c_temp;
	string input_str = "";
	while (input.get(c_temp)){
		input_str += c_temp;
	}
	string search_str = "ego";

	for (int i = 0; i < input_str.size()-search_str.size()+1 ;i++){
		table.insert(input_str.c_str(), i, i+search_str.size());
	}

	table.search_all(search_str.c_str());

	input.close();
	return 0;
}

int code_integer_casting(const char* s){
	int code = 0;
	int n;
	for(n=0;s+n && *(s+n) != '\0';n++) {}
	for(int i=0; i<4 && i<n; i++){
		code += (*(s+n-i-1))<<(8*i);
	}
	return code;
}
int code_component_sum(const char* s){
	int code = 0;
	int n;
	for(n=0;s+n && *(s+n) != '\0';n++) {}
	for(int i=0; i<n; i++){
		code += *(s+i);
	}
	return code;
}
int code_polynomial_sum(const char* s){
	int code = 0;
	int a = 33;
	int n;
	for(n=0;s+n && *(s+n) != '\0';n++) {}
	for(int i=0; i<n; i++){
		code = a*code + *(s+i);
	}
	return code;
}
int code_cyclic_sum(const char* s){
	int code = 0;
	int h = 5;
	int n;
	for(n=0;s+n && *(s+n) != '\0';n++) {}
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
int value_mad(int code, int m, int a, int b){
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

bool str_equal(const char* a, const char* b){
	int j=0;
	while(*(a+j) == *(b+j)){
		if (*(a+j) == '\0'){
			return true;
		}
		j++;
	}
	return false;
}