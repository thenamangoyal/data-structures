#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

template <typename elem>
class slist;

template <typename elem>
class linkstack;

template <typename elem>
class slist {
	private:
	class node {
	public:
		elem val;
		node* next;
		node* prev;	
	};
public:
	slist();
	~slist();
	bool empty() const;
	void addfront(const elem& e);
	void removefront();
	const elem& front() const;
private:
	node* head;
};

template <typename elem>
slist<elem>::slist() : head(NULL) {}

template <typename elem>
slist<elem>::~slist() {
	while (!empty()){
		removefront();
	}
}

template <typename elem>
bool slist<elem>::empty() const{
	return (head== NULL);
}

template <typename elem>
void slist<elem>::addfront(const elem& e){
	node* toadd = new node;
	toadd->val = e;
	toadd->next = head;
	head = toadd;
}

template <typename elem>
void slist<elem>::removefront() {
	node* torem = head;
	head = head->next;
	delete torem; 
}

template <typename elem>
const elem& slist<elem>::front() const{
	return (head->val);
}


template <typename elem>
class linkstack{
public:
	linkstack();
	~linkstack();
	int size() const;
	bool empty() const;
	void push(const elem& e);
	void pop();
	const elem& top() const;

private:
	slist<elem> l;
	int n;
};

template <typename elem>
linkstack<elem>::linkstack(): l(),n(0) {}

template <typename elem>
linkstack<elem>::~linkstack() {}

template <typename elem>
int linkstack<elem>::size() const{
	return n;
}

template <typename elem>
bool linkstack<elem>::empty() const{
	return (n==0);
}

template <typename elem>
void linkstack<elem>::push(const elem& e){
	l.addfront(e);
	n++;
}

template <typename elem>
void linkstack<elem>::pop(){
	l.removefront();
	n--;
}

template <typename elem>
const elem& linkstack<elem>::top() const{
	return (l.front());
}

int main(){

	ifstream input;
	input.open("input2.txt",ios::in);
	string line;

	ofstream output;
	output.open("2015csb1021-output2.txt", ios::out | ios::trunc);

	while(getline(input,line)){
		stringstream input_stream(line);

		vector<int> inArray;
		vector<int> ans;
		linkstack<int> s;
		int n=0;
		
		int temp;
		while(input_stream>>temp){
			inArray.push_back(temp);
			n++;
		}
		

		for(int i=0; i<n ; i++){
			while (!s.empty() && inArray[i] > s.top()){
				s.pop();
			}
			if (s.empty()){
				ans.push_back(-1);
			}
			else {
				ans.push_back(s.top());
			}
			s.push(inArray[i]);		
		}

		for(int k=0; k<n;k++){
			output<<ans[k];
			if (k<n-1){
				output<<" ";
			}
			else if (k == n-1){
				output<<endl;
			}
		}
	}
	input.close();
	output.close();
	return 0;
}