#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <list>
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

class hash_table {
private:
	list<hash_entry> *table;
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
	void insert(const char* v_key, int v_start_index, int v_end_index);
	void search_all(ofstream& output, const char* v_key, int& no_comp, int& no_false_pos);
};

void final_print_comp(ofstream& output, long long int search_no_comp[][3]);
void final_print_false_pos(ofstream& output, long long int search_no_false_pos[][3]);
void print_comp(ofstream& output, int search_no_comp[][3]);
void print_false_pos(ofstream& output, int search_no_false_pos[][3]);

int hash_code(const char* s, int code_no);
int code_integer_casting(const char* s);
int code_component_sum(const char* s);
int code_polynomial_sum(const char* s);
int code_cyclic_sum(const char* s);

int hash_value(int hash_code, int m, int value_no);
int value_division(int code, int m);
int value_mad(int code, int m);
int value_multiplication(int code, int m);

int str_len(const char* a);
bool str_equal(const char* a, const char* b);

hash_table::hash_table(int v_code_no, int v_value_no, int v_capacity){
	code_no = v_code_no;
	value_no = v_value_no;
	size = 0;
	capacity = v_capacity;
	if (capacity > 0){
		table = new list<hash_entry>[capacity];
	}
	else {
		table = NULL;
	}

}

hash_table::~hash_table(){
	if (table != NULL) {
		// Deleting old table
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
	hash_entry h = hash_entry(v_key, v_start_index, v_end_index);
	int code = hash_code(h.getkey(), code_no);
	int value = hash_value(code, capacity, value_no);
	table[value].push_front(h);
	size++;
}


void hash_table::search_all(ofstream& output, const char* v_key, int& no_comp, int& no_false_pos){
	
	if (code_no == 2 && value_no == 2){
		//cout<<"Pattern: "<<v_key<<endl;
		output<<"Pattern: "<<v_key<<endl;
	}

	no_comp = 0;
	no_false_pos = 0;

	int code = hash_code(v_key, code_no);
	int value = hash_value(code, capacity, value_no);
	int counter = 0;
	
	for(list<hash_entry>::iterator i = table[value].begin(); i != table[value].end(); i++){
			char *p = i->getkey();
			bool isEqual = str_equal(p,v_key);
			if (isEqual){
				// Pattern found				
				counter++;
				if (code_no == 2 && value_no == 2){
					//cout<<"Pattern found at index "<<table[index]->getstart_index()<<endl;
					output<<"Pattern found at index "<<i->getstart_index()<<endl;						
				}
			}
			else {
				// False positive
				no_false_pos++;
			}
			no_comp++;		
	}
	// Checked all cells
	if(code_no == 2 && value_no == 2){
		//cout<<endl;
		output<<endl;
		// Checked all cells
		if (counter == 0){
			//cout<<"Pattern not found"<<endl;
			output<<"Pattern not found"<<endl;
		}
		else if (counter == 1) {
			//cout<<counter<<" match found"<<endl;		
			output<<counter<<" match found"<<endl;		
		}	
		else {
			//cout<<counter<<" matches found"<<endl;
			output<<counter<<" matches found"<<endl;
		}
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

	clock_t start = clock();
	ofstream output;
	output.open("2015CSB1021Output1-chain.txt", ios::out | ios::trunc);
	ifstream input;
	ifstream pattern;
	input.open("T.txt",ios::in);
	pattern.open("P.txt",ios::in);	

	string input_str ((istreambuf_iterator<char>(input)), (istreambuf_iterator<char>()));	
	
	string line_pattern;
	cout<<"Running"<<endl;
	int no_comp;
	int no_false_pos;
	int counter = 0;
	int m=0;
	int n = input_str.size();
	int tab_size = (int)(floor((double)(n-m+1)/load_factor))+1;

	hash_table*** tab = new hash_table**[4];

	long long int final_no_comp[4][3];
	long long int final_no_false_pos[4][3];

	for (int i=0; i<4; i++){
		for(int j=0; j<3; j++){
			final_no_comp[i][j] = 0;
			final_no_false_pos[i][j] = 0;
		}
	}

	while(pattern>>line_pattern){
		if (counter == 0) {
			m = line_pattern.size();
			tab_size = (int)(floor((double)(n-m+1)/load_factor))+1;

			if (argc>=2){
				int req_tab_size = atoi(argv[1]);
				tab_size = (tab_size >= req_tab_size)? tab_size : req_tab_size;		
			}

			for (int i=0; i<4; i++){
				tab[i] = new hash_table*[3];
				for (int j=0; j<3; j++){
					tab[i][j] = new hash_table(i,j,tab_size);
				}
			}

			for (int i=0; i<n-m+1; i++){
				for (int j=0; j<4; j++){
					for (int k=0; k<3; k++){
						tab[j][k]->insert(input_str.c_str(), i, i+m);
					}
				}
			}
		}		
		
		int search_no_comp[4][3];
		int search_no_false_pos[4][3];
		for (int i=0; i<4; i++){
			for (int j=0; j<3; j++){
				tab[i][j]->search_all(output, line_pattern.c_str(), no_comp, no_false_pos);
				search_no_comp[i][j] = no_comp;
				search_no_false_pos[i][j] = no_false_pos;
				final_no_comp[i][j] += search_no_comp[i][j];
				final_no_false_pos[i][j] += search_no_false_pos[i][j];			
			}
		}
		
		print_comp(output, search_no_comp);
		print_false_pos(output, search_no_false_pos);
		//cout<<"--------------------"<<endl;
		output<<"--------------------"<<endl;
		counter++;
	}

	output<<endl<<"********************"<<endl;	
	cout<<"For all patterns"<<endl;
	output<<"For all patterns"<<endl;
	final_print_comp(output, final_no_comp);
	final_print_false_pos(output, final_no_false_pos);
	output<<endl<<"********************"<<endl;

	cout<<endl;
	output<<endl;
	cout<<"Search queries: "<<counter<<endl;
	cout<<"Hash table size: "<<tab[2][2]->getsize()<<" and capacity: "<<tab[2][2]->getcapacity()<<endl;
	output<<"Search queries: "<<counter<<endl;
	output<<"Hash table size: "<<tab[2][2]->getsize()<<" and capacity: "<<tab[2][2]->getcapacity()<<endl;
	
	for (int i=0; i<4; i++){	
		for (int j=0; j<3; j++){
			delete tab[i][j];
		}
		delete [] tab[i];
	}
	delete [] tab;

	clock_t end = clock();

	double time = double (end-start)/ CLOCKS_PER_SEC;
	cout<<"Running time: "<<time<<endl;
	output<<"Running time: "<<time<<endl;

	input.close();
	pattern.close();
	output.close();

	return 0;
}


void final_print_comp(ofstream& output, long long int search_no_comp[][3]){
	cout<<endl;
	cout<<"Total no of Comparisons"<<endl;
	output<<endl;
	output<<"Total no of Comparisons"<<endl;
	for (int i=0; i<4;i++){
		for(int j=0; j<3; j++){
			cout<<search_no_comp[i][j]<<" ";
			output<<search_no_comp[i][j]<<" ";
		}
		cout<<endl;
		output<<endl;
	}
}

void final_print_false_pos(ofstream& output, long long int search_no_false_pos[][3]){
	cout<<endl;
	cout<<"Total no of False positives"<<endl;
	output<<endl;
	output<<"Total no of False positives"<<endl;
	for (int i=0; i<4;i++){
		for(int j=0; j<3; j++){
			cout<<search_no_false_pos[i][j]<<" ";
			output<<search_no_false_pos[i][j]<<" ";
		}
		cout<<endl;
		output<<endl;
	}
}

void print_comp(ofstream& output, int search_no_comp[][3]){
	//cout<<endl;
	//cout<<"Comparisons"<<endl;
	output<<endl;
	output<<"Comparisons"<<endl;
	for (int i=0; i<4;i++){
		for(int j=0; j<3; j++){
			//cout<<search_no_comp[i][j]<<" ";
			output<<search_no_comp[i][j]<<" ";
		}
		//cout<<endl;
		output<<endl;
	}
}

void print_false_pos(ofstream& output, int search_no_false_pos[][3]){
	//cout<<endl;
	//cout<<"False positives"<<endl;
	output<<endl;
	output<<"False positives"<<endl;
	for (int i=0; i<4;i++){
		for(int j=0; j<3; j++){
			//cout<<search_no_false_pos[i][j]<<" ";
			output<<search_no_false_pos[i][j]<<" ";
		}
		//cout<<endl;
		output<<endl;
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

int str_len(const char* a){
	int i;
	for(i=0; a[i] != '\0'; i++){}
	return i;
}