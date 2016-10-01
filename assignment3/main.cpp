#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

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
	int code_no;
	int value_no;
public:
	hash_table(int v_code_no = 2, int v_value_no = 2, int v_capacity=0);
	void rehash();
	int getsize() const;
	void insert(const char* v_key, int v_start_index, int v_end_index);
	void search_all(const char* v_key, int& no_comp, int& no_false_pos);
};

int hash_code(const char* s, int code_no);
int code_integer_casting(const char* s);
int code_component_sum(const char* s);
int code_polynomial_sum(const char* s);
int code_cyclic_sum(const char* s);

int hash_value(int hash_code, int m, int value_no);
int value_division(int code, int m);
int value_mad(int code, int m);
int value_multiplication(int code, int m);

int linear_probe_index(int value, int i, int m);

int str_len(const char* a);
bool str_equal(const char* a, const char* b);

hash_table::hash_table(int v_code_no, int v_value_no, int v_capacity){
	code_no = v_code_no;
	value_no = v_value_no;
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
	
	if (size>=capacity) {
		rehash();
	}

	hash_entry* h = new hash_entry(v_key, v_start_index, v_end_index);
	int code = hash_code(h->getkey(), code_no);
	int value = hash_value(code, capacity, value_no);
	int index;
	int i;
	for(i=0; i<capacity; i++){
		index = linear_probe_index(value, i, capacity);
		if (table[index] == NULL){
			// Found an empty cell
			size++;
			table[index] = h;
			break;
		}
	}
	
}

void hash_table::rehash(){	
	int new_capacity = (2*capacity > 1)? (2*capacity): 1;
	int new_size = 0;
	hash_entry** new_table = new hash_entry*[new_capacity];
	for (int i=0; i< new_capacity; i++){
		new_table[i] = NULL;
	}

	int new_code;
	int new_value;
	int index;

	for (int i=0 ; i< capacity; i++){
		new_code = hash_code(table[i]->getkey(), code_no);
		new_value = hash_value(new_code, new_capacity, value_no);
		index;
		for(int j=0; j<new_capacity; j++){
			index = linear_probe_index(new_value, j, new_capacity);
			if (new_table[index] == NULL){
				// Found an empty cell
				new_size++;
				new_table[index] = new hash_entry(*table[i]);
				break;
			}
		}

	}
	if (table != NULL) {
		// Deleting old table
		for (int i =0 ; i< capacity; i++){
			delete table[i];
		}
		delete [] table;
		
	}
	table = new_table;
	capacity = new_capacity;
	size = new_size;
}


void hash_table::search_all(const char* v_key, int& no_comp, int& no_false_pos){
	//cout<<"Capacity: "<<capacity<<" Size: "<<size<<endl;
	no_comp = 0;
	no_false_pos = 0;
	int code = hash_code(v_key, code_no);
	int value = hash_value(code, capacity, value_no);
	int index;
	bool found = false;
	for(int i=0; i<capacity; i++){
		index = linear_probe_index(value, i, capacity);
		if (table[index]){
			char *p = table[index]->getkey();
			bool isEqual = str_equal(p,v_key);
			if (isEqual){
				found = true;
				cout<<"Pattern found at index "<<table[index]->getstart_index()<<endl;
			}
			else {
				// False positive
				no_false_pos++;
			}
			no_comp++;
		}
		else {
			// Found an empty cell
			if (!found){
				cout<<"Couldn't find the Pattern"<<endl;
			}
			return;
		}
	}

	if (!found) {
		// Checked all cells but result not found
		cout<<"Couldn't find the Pattern"<<endl;
	}	

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

	hash_table table;

	ifstream input;
	ifstream pattern;
	input.open("T.txt",ios::in);
	pattern.open("P.txt",ios::in);
	
	string input_str ((istreambuf_iterator<char>(input)), (istreambuf_iterator<char>()));	
	
	int m = 6;
	int n = input_str.size();

	for (int i = 0; i < n-m+1 ;i++){
		table.insert(input_str.c_str(), i, i+m);
	}

	string line_pattern;
	
	int no_comp;
	int no_false_pos;
	while(pattern>>line_pattern){
		cout<<"Pattern: "<<line_pattern<<endl;
		table.search_all(line_pattern.c_str(), no_comp, no_false_pos);
		cout<<"Comparisons: "<<no_comp<<" False positives: "<<no_false_pos<<endl;
		cout<<"-------------------"<<endl;
	}
	input.close();
	pattern.close();
	
	return 0;
}

int hash_code(const char* s, int code_no){
	int code = 0;
	switch(code_no){
		case 0:
			code = code_integer_casting(s);
			break;
		case 1:
			code = code_component_sum(s);
			break;
		case 2:
			code = code_polynomial_sum(s);
			break;
		case 3:
			code = code_cyclic_sum(s);
			break;
	}
	return code;
}

int code_integer_casting(const char* s){
	int code = 0;
	int n = str_len(s);
	for(int i=0; i<4 && i<n; i++){
		code += s[n-i-1]<<(8*i);
	}
	return code;
}
int code_component_sum(const char* s){
	int code = 0;
	int n = str_len(s);
	for(int i=0; i<n; i++){
		code += s[i];
	}
	return code;
}
int code_polynomial_sum(const char* s){
	int code = 0;
	int a = 33;	
	int n = str_len(s);
	for(int i=0; i<n; i++){
		code = a*code + s[i];
	}
	return code;
}
int code_cyclic_sum(const char* s){
	int code = 0;
	int h = 5;
	int n = str_len(s);
	for(int i=0; i<n; i++){
		code = (code<<h)+ (code>>(32-h));
		code += s[i];
	}
	return code;
}


int hash_value(int hash_code, int m, int value_no){
	int value = 0;
	switch(value_no){
		case 0:
			value = value_division(hash_code, m);
			break;
		case 1:
			value = value_mad(hash_code, m);
			break;
		case 2:
			value = value_multiplication(hash_code, m);
			break;
	}
	return value;
}

int value_division(int code, int m){
	code = (code >= 0)? code : (-1)*code;
	return (code%m);
}
int value_mad(int code, int m){
	code = (code >= 0)? code : (-1)*code;
	int a = (int)(floor(sqrt((double)m)));	
	int b = m/2;
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

int linear_probe_index(int value, int i, int m){
	return (value+i)%m;
}

bool str_equal(const char* a, const char* b){
	int i=0;
	while( a[i] == b[i]){
		if (a[i] == '\0'){
			return true;
		}
		i++;
	}
	return false;
}

int str_len(const char* a){
	int i;
	for(i=0; a[i] != '\0'; i++){}
	return i;
}