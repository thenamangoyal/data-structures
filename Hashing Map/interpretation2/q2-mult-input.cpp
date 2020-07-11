#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>

#define load_factor 0.5
using namespace std;

class hash_entry{
private:
	char* key;
	int start_index;
	int end_index;
	int hash;
public:
	hash_entry(const char* v_key, int v_start_index, int v_end_index, int v_hash);
	hash_entry(const hash_entry& h);
	char* getkey() const;
	int getstart_index() const;
	int getend_index() const;
	int gethash() const;
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
	~hash_table();
	void rehash();
	int getsize() const;
	int getcapacity() const;
	int getcode_no() const;
	int getvalue_no() const;
	void setcode_no(int v_code_no);
	void setvalue_no(int v_value_no);
	void insert(const char* v_key, int v_start_index, int v_end_index);
	void search_all(ofstream& output, const char* v_key, int& no_comp, int& no_false_pos);
};

void print_code_no(ofstream& output, int code_no);
void print_value_no(ofstream& output, int value_no);

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

hash_table::~hash_table(){
	if (table != NULL) {
		// Deleting old table
		for (int i =0 ; i< capacity; i++){
			if (table[i]){
				delete table[i];
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

void hash_table::insert(const char* v_key, int v_start_index, int v_end_index){
	int exp_size = (int)(floor(load_factor*(double)capacity));
	if (size>=exp_size) {
		rehash();
	}

	char* insert_key = new char[v_end_index-v_start_index+1];
	for(int i=v_start_index; i < v_end_index; i++){
		*(insert_key+i-v_start_index) = *(v_key+i);
	}
	*(insert_key+v_end_index-v_start_index) = '\0';

	int code = hash_code(insert_key, code_no);
	int value = hash_value(code, capacity, value_no);
	
	int index;
	for(int i=0; i<capacity; i++){
		index = linear_probe_index(value, i, capacity);
		if (table[index] == NULL){
			// Found an empty cell
			size++;
			table[index] = new hash_entry(insert_key, v_start_index, v_end_index, value);
			break;
		}
	}
	delete [] insert_key;
	
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
		if (table[i]){
			new_code = hash_code(table[i]->getkey(), code_no);
			new_value = hash_value(new_code, new_capacity, value_no);
			for(int j=0; j<new_capacity; j++){
				index = linear_probe_index(new_value, j, new_capacity);
				if (new_table[index] == NULL){
					// Found an empty cell
					new_size++;
					new_table[index] = new hash_entry(table[i]->getkey(), table[i]->getstart_index(), table[i]->getend_index(), new_value);
					break;
				}
			}
		}

	}
	if (table != NULL) {
		// Deleting old table
		for (int i =0 ; i< capacity; i++){
			if (table[i]){
				delete table[i];
			}
		}
		delete [] table;
		
	}
	table = new_table;
	capacity = new_capacity;
	size = new_size;
}

void hash_table::search_all(ofstream& output, const char* v_key, int& no_comp, int& no_false_pos){	

	int n = str_len(v_key);

	char* search_key = new char[n];

	for(int i=0; i< n; i++){
		search_key[i] = v_key[i];
	}

	int counter = 0;

	no_comp = 0;
	no_false_pos = 0;

	int index;

	int pos = -1;

	for(int i=0; i<n; i++){
		if(search_key[i] == '?'){
			pos = i;
			break;
		}
	}

	if(pos>= 0){
		for(int j=1; j <= 127; j++){
			search_key[pos] = j;

			int code = hash_code(search_key, code_no);
			int value = hash_value(code, capacity, value_no);

			for(int i=0; i<capacity; i++){
				index = linear_probe_index(value, i, capacity);
				if (table[index]){
					if (table[index]->gethash() == value){
						char *p = table[index]->getkey();
						bool isEqual = str_equal(p,search_key);
						if (isEqual){
							// Pattern found
							counter++;								
							cout<<"Pattern "<<p<<" found at index "<<table[index]->getstart_index()<<endl;
							output<<"Pattern "<<p<<" found at index "<<table[index]->getstart_index()<<endl;						
							
						}
						else {
							// False positive
							no_false_pos++;
						}
						no_comp++;
					}
					
				}
				else {
					// Found an empty cell			
					break;
				}
			}			
			
		}

	}
	else {
		int code = hash_code(search_key, code_no);
		int value = hash_value(code, capacity, value_no);

		for(int i=0; i<capacity; i++){
			index = linear_probe_index(value, i, capacity);
			if (table[index]){
				if (table[index]->gethash() == value){
					char *p = table[index]->getkey();
					bool isEqual = str_equal(p,search_key);
					if (isEqual){
						// Pattern found
						counter++;								
						cout<<"Pattern "<<p<<" found at index "<<table[index]->getstart_index()<<endl;
						output<<"Pattern "<<p<<" found at index "<<table[index]->getstart_index()<<endl;						
						
					}
					else {
						// False positive
						no_false_pos++;
					}
					no_comp++;
				}
				
			}
			else {
				// Found an empty cell			
				break;
			}
		}
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

}

hash_entry::hash_entry(const char* v_key, int v_start_index, int v_end_index, int v_hash){
	start_index = v_start_index;
	end_index = v_end_index;
	hash = v_hash;
	key = new char[v_end_index-v_start_index+1];
	for(int i=0; i < v_end_index-v_start_index; i++){
		*(key+i) = *(v_key+i);
	}
	*(key+v_end_index-v_start_index) = '\0';
}

hash_entry::hash_entry(const hash_entry& h){
	start_index = h.start_index;
	end_index = h.end_index;
	hash = h.hash;
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
int hash_entry::gethash() const{
	return hash;
}



int main(int argc, char const *argv[]){	
	
	clock_t start = clock();
	ofstream output;
	output.open("2015CSB1021Output2-mult-input.txt", ios::out | ios::trunc);
	ifstream input;
	ifstream pattern;
	input.open("T2.txt",ios::in);
	pattern.open("P2.txt",ios::in);	

	string input_str ((istreambuf_iterator<char>(input)), (istreambuf_iterator<char>()));	
	
	string line_pattern;
	cout<<"Running"<<endl;
	int no_comp;
	int no_false_pos;
	int counter = 0;
	int m=0;
	int n = input_str.size();

	int tab_size = (int)(floor((double)(n-m+1)/load_factor))+1;
	int default_code_no = 2;
	int default_value_no = 2;

	hash_table* tab;

	long long int final_no_comp = 0;
	long long int final_no_false_pos = 0;

	while(pattern>>line_pattern){
		if (counter == 0) {
			m = line_pattern.size();
			tab_size = (int)(floor((double)(n-m+1)/load_factor))+1;

			if (argc>=2){
				int req_tab_size = atoi(argv[1]);
				tab_size = (tab_size >= req_tab_size)? tab_size : req_tab_size;		
			}
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

			tab = new hash_table(default_code_no, default_value_no, tab_size);
			
			for (int i=0; i<n-m+1; i++){
				tab->insert(input_str.c_str(), i, i+m);
			}
		}
		
		cout<<"Pattern: "<<line_pattern<<endl;
		output<<"Pattern: "<<line_pattern<<endl;
		
		tab->search_all(output, line_pattern.c_str(), no_comp, no_false_pos);

		cout<<endl;
		output<<endl;
		cout<<"Comparisons: "<<no_comp<<endl;		
		output<<"Comparisons: "<<no_comp<<endl;
		
		
		cout<<"False positives: "<<no_false_pos<<endl;		
		output<<"False positives: "<<no_false_pos<<endl;
		cout<<"--------------------"<<endl;
		output<<"--------------------"<<endl;

		final_no_comp += no_comp;
		final_no_false_pos += no_false_pos;
		counter++;
	}
	
	cout<<endl;
	output<<endl;
	cout<<"For all patterns"<<endl;
	output<<"For all patterns"<<endl;		

	cout<<endl;
	output<<endl;
	cout<<"Total no of Comparisons: "<<final_no_comp<<endl;	
	output<<"Total no of Comparisons: "<<final_no_comp<<endl;

	cout<<"Total no of False positives: "<<final_no_false_pos<<endl;
	output<<"Total no of False positives: "<<final_no_false_pos<<endl;

	
	cout<<endl;
	output<<endl;
	cout<<"Search queries: "<<counter<<endl;
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
	pattern.close();
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
		code = (code<<h) | (code>>(32-h));
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
	int b = (int)(floor(sqrt((double)m))) + 1;
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