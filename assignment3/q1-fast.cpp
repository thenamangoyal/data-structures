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
	void insert(const char* v_key, int v_start_index, int v_end_index);
	vector<hash_entry> search_all(const char* v_key, int& no_comp, int& no_false_pos);
};

void print_index(ofstream& output, vector< vector< vector<int> > > search_start_index);
void print_comp(ofstream& output, vector< vector<int> > search_no_comp);
void print_false_pos(ofstream& output, vector< vector<int> > search_no_false_pos);

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

void hash_table::insert(const char* v_key, int v_start_index, int v_end_index){	
	hash_entry h = hash_entry(v_key, v_start_index, v_end_index);
	int code = hash_code(h.getkey(), code_no);
	int value = hash_value(code, capacity, value_no);
	table[value].push_front(h);
	size++;
}


vector<hash_entry> hash_table::search_all(const char* v_key, int& no_comp, int& no_false_pos){
	//cout<<"Capacity: "<<capacity<<" Size: "<<size<<endl;
	vector<hash_entry> ans;
	no_comp = 0;
	no_false_pos = 0;
	int code = hash_code(v_key, code_no);
	//cout<<code<<endl;
	int value = hash_value(code, capacity, value_no);
	//cout<<value<<endl;	
	
	for(list<hash_entry>::iterator i = table[value].begin(); i != table[value].end(); i++){
			char *p = i->getkey();
			bool isEqual = str_equal(p,v_key);
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



int main(){


	ofstream output;
	output.open("2015CSB1021Output1-fast.txt", ios::out | ios::trunc);
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
	int m;
	int n = input_str.size();

	vector< vector<hash_table> > tab (4, vector<hash_table>(3));
	

	while(pattern>>line_pattern){
		if (counter == 0) {
			m = line_pattern.size();
			int tab_size = (int)(ceil((double)(n-m+1)/load_factor));
			for (int i=0; i<4; i++){
				for (int j=0; j<3; j++){
					tab[i][j] = hash_table(i,j,tab_size);
				}
			}	
			for (int i=0; i<n-m+1; i++){
				for (int j=0; j<4; j++){					
					for (int k=0; k<3; k++){
						tab[j][k].insert(input_str.c_str(), i, i+m);
					}
				}
			}
		}
		cout<<"Pattern: "<<line_pattern<<endl;
		output<<"Pattern: "<<line_pattern<<endl;
		vector< vector< vector<hash_entry> > > search_entry(4, vector< vector<hash_entry> >(3));
		vector< vector< vector<int> > > search_start_index(4, vector< vector<int> >(3));
		vector< vector<int> > search_no_comp(4, vector<int>(3));
		vector< vector<int> > search_no_false_pos(4, vector<int>(3));
		for (int i=0; i<4; i++){
			for (int j=0; j<3; j++){
				search_entry[i][j] = (tab[i][j].search_all(line_pattern.c_str(), no_comp, no_false_pos));
				for(int k=0; k< search_entry[i][j].size(); k++){
					search_start_index[i][j].push_back(search_entry[i][j][k].getstart_index());
				}
				sort(search_start_index[i][j].begin(), search_start_index[i][j].end());
				search_no_comp[i][j] = no_comp;
				search_no_false_pos[i][j] = no_false_pos;				
			}
		}
		print_index(output, search_start_index);
		print_comp(output, search_no_comp);
		print_false_pos(output, search_no_false_pos);
		cout<<"--------------------"<<endl;
		output<<"--------------------"<<endl;
		counter++;
	}

	input.close();
	pattern.close();
	output.close();
	return 0;
}

void print_index(ofstream& output, vector< vector< vector<int> > > search_start_index){
	bool match = true;
	for (int i =0 ; i<11; i++){
		if (search_start_index[i/3][i%3] != search_start_index[(i+1)/3][(i+1)%3]){
			match = false;
			break;
		}
	}
	if (match && !(search_start_index[0][0].empty())){
		cout<<endl;
		output<<endl;
		for (int i=0; i< search_start_index[0][0].size(); i++){
			cout<<"Pattern found at index "<<search_start_index[0][0][i]<<endl;
			output<<"Pattern found at index "<<search_start_index[0][0][i]<<endl;
		}
	}
}
void print_comp(ofstream& output, vector< vector<int> > search_no_comp){
	cout<<endl;
	cout<<"Comparisons"<<endl;
	output<<endl;
	output<<"Comparisons"<<endl;
	for (int i=0; i<4;i++){
		for(int j=0; j<3; j++){
			cout<<search_no_comp[i][j]<<" ";
			output<<search_no_comp[i][j]<<" ";
		}
		cout<<endl;
		output<<endl;
	}
}
void print_false_pos(ofstream& output, vector< vector<int> > search_no_false_pos){
	cout<<endl;
	cout<<"False positives"<<endl;
	output<<endl;
	output<<"False positives"<<endl;
	for (int i=0; i<4;i++){
		for(int j=0; j<3; j++){
			cout<<search_no_false_pos[i][j]<<" ";
			output<<search_no_false_pos[i][j]<<" ";
		}
		cout<<endl;
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