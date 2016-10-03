#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

#define load_factor 0.9
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
	vector< list<hash_entry> > table;
	int capacity;
	int size;
	int code_no;
	int value_no;
public:
	hash_table(int v_code_no = 2, int v_value_no = 2, int v_capacity=1);
	~hash_table();
	int getsize() const;
	int getcapacity() const;
	int getcode_no() const;
	int getvalue_no() const;
	void setcode_no(int v_code_no);
	void setvalue_no(int v_value_no);
	void insert(const char* v_key, const char* search_key, int v_start_index, int v_end_index);
	vector<hash_entry> search_all(const char* v_key, int& no_comp, int& no_false_pos);
};

int hash_code(const char* s, const char* search_key, int code_no);
int code_integer_casting(const char* s, const char* search_key);
int code_component_sum(const char* s, const char* search_key);
int code_polynomial_sum(const char* s, const char* search_key);
int code_cyclic_sum(const char* s, const char* search_key);

int hash_value(int hash_code, int m, int value_no);
int value_division(int code, int m);
int value_mad(int code, int m);
int value_multiplication(int code, int m);

int str_len(const char* a);
bool str_equal(const char* a, const char* b);
bool str_equal_2(const char* a, const char* b);

hash_table::hash_table(int v_code_no, int v_value_no, int v_capacity){
	code_no = v_code_no;
	value_no = v_value_no;
	size = 0;
	capacity = v_capacity;
	list<hash_entry> l_temp;
	table = vector< list<hash_entry> >(v_capacity);

}

hash_table::~hash_table(){
}


int hash_table::getsize() const{
	return size;
}

int hash_table::getcapacity() const{
	return capacity;
}

int hash_table::getcode_no() const{
	return code_no;
}
int hash_table::getvalue_no() const{
	return value_no;
}

void hash_table::setcode_no(int v_code_no){
	code_no = v_code_no;
}
void hash_table::setvalue_no(int v_value_no){
	value_no = v_value_no;
}

void hash_table::insert(const char* v_key, const char* search_key, int v_start_index, int v_end_index){	
	hash_entry h = hash_entry(v_key, v_start_index, v_end_index);
	int code = hash_code(h.getkey(), search_key, code_no);
	int value = hash_value(code, capacity, value_no);
	table[value].push_front(h);
	size++;
}


vector<hash_entry> hash_table::search_all(const char* v_key, int& no_comp, int& no_false_pos){
	//cout<<"Capacity: "<<capacity<<" Size: "<<size<<endl;
	vector<hash_entry> ans;
	no_comp = 0;
	no_false_pos = 0;
	int code = hash_code(v_key, v_key, code_no);
	//cout<<code<<endl;
	int value = hash_value(code, capacity, value_no);
	//cout<<value<<endl;	
	
	for(list<hash_entry>::iterator i = table[value].begin(); i != table[value].end(); i++){
			char *p = i->getkey();
			bool isEqual = str_equal_2(p,v_key);
			if (isEqual){
				// Pattern found
				ans.push_back(*i);
			}
			else {
				// False positive
				no_false_pos++;
			}
			no_comp++;		
	}	
	// Checked all cells
	return ans;

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

int main(int argc, char const *argv[]){

	if (argc < 2){
		cout<<"Please provide search string as an argument."<<endl;
		return 0;
	}
	ofstream output;
	output.open("2015CSB1021Output2-chain.txt", ios::out | ios::trunc);
	ifstream input;
	input.open("T2.txt",ios::in);

	string input_str ((istreambuf_iterator<char>(input)), (istreambuf_iterator<char>()));	
	
	const char* line_pattern = argv[1];

	int no_comp;
	int no_false_pos;
	int m = str_len(line_pattern);
	int n = input_str.size();
	
	int tab_size = 1;
	int default_code_no = 2;
	int default_value_no = 2;

	tab_size = (int)(ceil((double)(n-m+1)/load_factor));

	if (argc>=3){
		if (argv[2][0] >= '0' && argv[2][0] <= '3'){
			default_code_no = argv[2][0] - '0';
		}
	}
	if (argc>=4){
		if (argv[3][0] >= '0' && argv[3][0] <= '2'){
			default_value_no = argv[3][0] - '0';
		}
	}

	if (argc>=5){
		int req_tab_size = atoi(argv[4]);
		tab_size = (tab_size >= req_tab_size)? tab_size : req_tab_size;
	}

	hash_table tab(default_code_no,default_value_no, tab_size);
	
	for (int i=0; i<n-m+1; i++){
		tab.insert(input_str.c_str(), line_pattern, i, i+m);
	}
	
	cout<<"Pattern: "<<line_pattern<<endl<<endl;
	output<<"Pattern: "<<line_pattern<<endl<<endl;

	vector<hash_entry> search_entry;			
	search_entry = tab.search_all(line_pattern, no_comp, no_false_pos);

	if (!(search_entry.empty())){
		if (search_entry.size() == 1) {
			cout<<search_entry.size()<<" match found"<<endl;
			cout<<endl;
			output<<search_entry.size()<<" match found"<<endl;
			output<<endl;
		}
		else {
			cout<<search_entry.size()<<" matches found"<<endl;
			cout<<endl;
			output<<search_entry.size()<<" matches found"<<endl;
			output<<endl;
		}
		
		
		for (int i=0; i< search_entry.size(); i++){
			cout<<"Pattern "<<search_entry[i].getkey()<<" found at index "<<search_entry[i].getstart_index()<<endl;
			output<<"Pattern "<<search_entry[i].getkey()<<" found at index "<<search_entry[i].getstart_index()<<endl;
		}
	}
	else {
		cout<<"Pattern not found"<<endl;
		output<<"Pattern not found"<<endl;
	}
	cout<<endl;
	cout<<"Comparisons: "<<no_comp<<endl;
	output<<endl;
	output<<"Comparisons: "<<no_comp<<endl;
	
	cout<<endl;
	cout<<"False positives: "<<no_false_pos<<endl;
	output<<endl;
	output<<"False positives: "<<no_false_pos<<endl;

	cout<<endl;
	output<<endl;
	cout<<"Hash table size: "<<tab[2][2].getsize()<<" and capacity: "<<tab[2][2].getcapacity()<<endl;
	output<<"Hash table size: "<<tab[2][2].getsize()<<" and capacity: "<<tab[2][2].getcapacity()<<endl;

	input.close();
	output.close();
	return 0;
}

int hash_code(const char* s, const char* search_key, int code_no){
	int code = 0;
	switch(code_no){
		case 0:
			code = code_integer_casting(s, search_key);
			break;
		case 1:
			code = code_component_sum(s, search_key);
			break;
		case 2:
			code = code_polynomial_sum(s, search_key);
			break;
		case 3:
			code = code_cyclic_sum(s, search_key);
			break;
	}
	return code;
}

int code_integer_casting(const char* s, const char* search_key){
	int code = 0;
	int n1 = str_len(s);
	int n2 = str_len(search_key);
	if (n1 == n2){
		for(int i=0; i<4 && i<n1; i++){
			if (search_key[n1-i-1] != '?'){
				code += s[n1-i-1]<<(8*i);
			}
		}
	}
	return code;
}
int code_component_sum(const char* s, const char* search_key){
	int code = 0;
	int n1 = str_len(s);
	int n2 = str_len(search_key);
	if (n1 == n2){
		for(int i=0; i<n1; i++){
			if (search_key[i] != '?'){
				code += s[i];
			}
		}
	}
	return code;
}
int code_polynomial_sum(const char* s, const char* search_key){
	int code = 0;
	int a = 33;	
	int n1 = str_len(s);
	int n2 = str_len(search_key);
	if (n1 == n2){
		for(int i=0; i<n1; i++){
			if (search_key[i] != '?'){
				code = a*code + s[i];
			}
		}
	}
	return code;
}
int code_cyclic_sum(const char* s, const char* search_key){
	int code = 0;
	int h = 5;
	int n1 = str_len(s);
	int n2 = str_len(search_key);
	if (n1 == n2){
		for(int i=0; i<n1; i++){
			code = (code<<h)+ (code>>(32-h));
			if (search_key[i] != '?'){				
				code += s[i];
			}
		}
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

bool str_equal_2(const char* a, const char* b){
	
	if (str_len(a) == str_len(b)){
		int i=0;
		while(b[i] == '?' || a[i] == b[i]){
			if (b[i] == '\0'){
				return true;
			}
			i++;
		}
	}
	
	return false;
}

int str_len(const char* a){
	int i;
	for(i=0; a[i] != '\0'; i++){}
	return i;
}