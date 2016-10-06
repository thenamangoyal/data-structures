#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>

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

class node{
public:
	hash_entry entry;
	node* next;
public:
	node(const hash_entry& h, node* v_next = NULL);
	~node();
};

node::node(const hash_entry& h, node* v_next): entry(h), next(v_next) {}

node::~node(){
}

class linklist{
public:
	node* head;
	node* tail;
};

class hash_table {
private:
	linklist* table;
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
	void search_all(ofstream& output, const char* v_key, int& no_comp, int& no_false_pos);
};

void print_code_no(ofstream& output, int code_no);
void print_value_no(ofstream& output, int value_no);

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
	if (capacity > 0){
		table = new linklist[capacity];
		for(int i=0; i<capacity; i++){
			table[i].head = NULL;
			table[i].tail = NULL;
		}
	}
	else {
		table = NULL;
	}

}

hash_table::~hash_table(){
	if (table != NULL) {
		// Deleting old table
		for(int i=0; i<capacity; i++){
			while(table[i].head){
				node* todel = table[i].head;
				table[i].head = (table[i].head)->next;
				delete todel;
			}
		}
		delete [] table;
	}
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
	
	node* toad = new node(h, NULL);

	if (table[value].head==NULL){
		table[value].head = table[value].tail = toad;
	}
	else{
		(table[value].tail)->next = toad;
		table[value].tail = toad;
	}

	size++;
}


void hash_table::search_all(ofstream& output, const char* v_key, int& no_comp, int& no_false_pos){
	
	no_comp = 0;

	int any_hash_value_match = 0;
	int ans_found = 0;

	int code = hash_code(v_key, v_key, code_no);
	int value = hash_value(code, capacity, value_no);

	int counter = 0;

	node* iter = table[value].head;

	while(iter){
			char *p = (iter->entry).getkey();
			bool isEqual = str_equal_2(p,v_key);
			if (isEqual){
				// Pattern found
				ans_found = 1;
				cout<<"Pattern "<<p<<" found at index "<<(iter->entry).getstart_index()<<endl;
				output<<"Pattern "<<p<<" found at index "<<(iter->entry).getstart_index()<<endl;
				counter++;
			}
			else {
				// False positive
			}
			any_hash_value_match = 1;
			no_comp++;
			iter = iter->next;	
	}
	cout<<endl;
	output<<endl;
	// Checked all cells
	if (counter == 0){
		cout<<"Pattern not found"<<endl;
		output<<"Pattern not found"<<endl;
	}
	else if (counter == 1) {
		cout<<counter<<" match found"<<endl;		
		output<<counter<<" match found"<<endl;		
	}	
	else {
		cout<<counter<<" matches found"<<endl;
		output<<counter<<" matches found"<<endl;
	}

	if (any_hash_value_match == 1){
			if (ans_found == 1){
				no_false_pos = 0;
			}
			else {
				no_false_pos = 1;
			}			
		}
	else{
		no_false_pos = 0;
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

int main(int argc, char const *argv[]){

	if (argc < 2){
		cout<<"Please provide search string as an argument."<<endl;
		return 0;
	}

	clock_t start = clock();

	ofstream output;
	output.open("2015CSB1021Output2-chain.txt", ios::out | ios::trunc);
	ifstream input;
	input.open("T2.txt",ios::in);

	string input_str ((istreambuf_iterator<char>(input)), (istreambuf_iterator<char>()));	
	
	const char* line_pattern = argv[1];
	cout<<"Running"<<endl;
	
	int no_comp;
	int no_false_pos;
	int m = str_len(line_pattern);
	int n = input_str.size();

	int tab_size = (int)(floor((double)(n-m+1)/load_factor))+1;
	int default_code_no = 2;
	int default_value_no = 2;

	if (argc>=3){
		int req_tab_size = atoi(argv[2]);
		tab_size = (tab_size >= req_tab_size)? tab_size : req_tab_size;		
	}
	if (argc>=4){
		if (argv[3][0] >= '0' && argv[3][0] <= '3'){
			default_code_no = argv[3][0] - '0';
		}
	}

	if (argc>=5){
		if (argv[4][0] >= '0' && argv[4][0] <= '2'){
			default_value_no = argv[4][0] - '0';
		}
	}

	hash_table* tab = new hash_table(default_code_no,default_value_no, tab_size);
	
	for (int i=0; i<n-m+1; i++){
		tab->insert(input_str.c_str(), line_pattern, i, i+m);
	}
	cout<<"Pattern: "<<line_pattern<<endl;
	output<<"Pattern: "<<line_pattern<<endl;
	
	tab->search_all(output, line_pattern, no_comp, no_false_pos);

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
	cout<<"Hash table size: "<<tab->getsize()<<" and capacity: "<<tab->getcapacity()<<endl;
	output<<"Hash table size: "<<tab->getsize()<<" and capacity: "<<tab->getcapacity()<<endl;

	print_code_no(output, tab->getcode_no());
	print_value_no(output, tab->getvalue_no());

	delete tab;

	clock_t end = clock();

	double time = double (end-start)/ CLOCKS_PER_SEC;
	cout<<"Running time: "<<time<<endl;
	output<<"Running time: "<<time<<endl;

	input.close();
	output.close();
	return 0;
}


void print_code_no(ofstream& output, int code_no){
	switch(code_no){
		case 0:
			cout<<"Hash code: Integer Casting"<<endl;
			output<<"Hash code: Integer Casting"<<endl;
			break;
		case 1:
			cout<<"Hash code: Component Sum"<<endl;
			output<<"Hash code: Component Sum"<<endl;
			break;
		case 2:
			cout<<"Hash code: Polynomial Sum"<<endl;
			output<<"Hash code: Polynomial Sum"<<endl;
			break;
		case 3:
			cout<<"Hash code: Cyclic Sum"<<endl;
			output<<"Hash code: Cyclic Sum"<<endl;
			break;
	}
}

void print_value_no(ofstream& output, int value_no){
	switch(value_no){
		case 0:
			cout<<"Hash function: Division"<<endl;
			output<<"Hash function: Division"<<endl;
			break;
		case 1:
			cout<<"Hash function: MAD"<<endl;
			output<<"Hash function: MAD"<<endl;
			break;
		case 2:
			cout<<"Hash function: Multiplication"<<endl;
			output<<"Hash function: Multiplication"<<endl;
			break;
	}
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
			code = (code<<h) | (code>>(32-h));
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