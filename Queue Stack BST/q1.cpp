#include <iostream>
#include <fstream>
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

bool isEcc();

int main(){
	if (isEcc()) {
		cout<<"True"<<endl;
	}
	else {
		cout<<"False"<<endl;
	}
	return 0;
}

bool isEcc() {
	ifstream input;
	input.open("input1.txt",ios::in);
	linkstack<char> s1;
	linkstack<char> s2;
	char temp;
	while(input.get(temp)){
		switch(temp){
			case '[': case '{': case '(':
			if (s1.empty()){
				s1.push(temp);
			}
			else if (s1.top() != '$') {
				s1.push(temp);
			}
			else if (s1.top() == '$') {
				s2.push(temp);
			}
			break;

			case ']': case '}': case ')':
			if (s1.empty()){
				return false;
			}
			else if (s1.top() != '$') {
				if (temp == ']' && s1.top() != '['){
					return false;
				}
				if (temp == '}' && s1.top() != '{'){
					return false;
				}
				if (temp == ')' && s1.top() != '('){
					return false;
				}
				s1.pop();
			}
			else if (s1.top() == '$') {
				if (s2.empty()){
					return false;
				}
				if (temp == ']' && s2.top() != '['){
					return false;
				}
				if (temp == '}' && s2.top() != '{'){
					return false;
				}
				if (temp == ')' && s2.top() != '('){
					return false;
				}
				s2.pop();
			}
			break;

			case '$':
			if (s1.empty()){
				s1.push(temp);
			}
			else if (s1.top() != '$'){
				s1.push(temp);
			}
			else if (s1.top() == '$'){
				if (!s2.empty()){
					return false;
				}
				s1.pop();
			}
			break;

		}
	}

	if (s1.empty() && s2.empty()){
		return true;
	}
	input.close();
	return false;
}