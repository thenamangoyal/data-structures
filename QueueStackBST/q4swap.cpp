#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

template <typename elem>
class dlist;

template <typename elem>
class linktree;

template <typename elem>
class dlist {
private:
	class node {
	public:
		elem val;
		node* next;
		node* prev;
	};
public:
	class Iterator {
		private:
			node* v;
			Iterator(node* u);
		public:
			elem& operator*();
			Iterator& operator--();
			Iterator& operator++();
			bool operator==(const Iterator& p) const;
			bool operator!=(const Iterator& p) const;
			friend class dlist<elem>;
	};
private:
	int n;
	node* header;
	node* trailer;
public:
	dlist();
	~dlist();
	bool empty() const;
	int size() const;
	const elem& front() const;
	const elem& back() const;
	void add(const Iterator& p, const elem& e);
	void remove(const Iterator& p);
	void addfront(const elem& e);
	void addback(const elem& e);
	void removeback();
	void removefront();
	void insertionSort();
	void remove_duplicates_sorted();
	Iterator begin();
	Iterator end();

protected:

};

template <typename elem>
dlist<elem>::dlist() {
	header  = new node();
	trailer = new node();
	header->next = trailer;
	trailer->prev = header;
	n = 0;
}

template <typename elem>
dlist<elem>::~dlist() {
	while(!empty()){
		removefront();
	}
	delete header;
	delete trailer;
}

template <typename elem>
bool dlist<elem>::empty() const{
	return (n == 0);
}

template <typename elem>
int dlist<elem>::size() const{
	return n;
}

template <typename elem>
const elem& dlist<elem>::front() const {
	return *(begin());
}

template <typename elem>
const elem& dlist<elem>::back() const{
	return *(--end());
}

template <typename elem>
void dlist<elem>::addfront(const elem& e){
	add(begin(),e);
}

template <typename elem>
void dlist<elem>::addback(const elem& e){
	add(end(),e);
}

template <typename elem>
void dlist<elem>::removeback(){
	remove(--end());
}

template <typename elem>
void dlist<elem>::removefront(){
	remove(begin());
}


template <typename elem>
void dlist<elem>::add(const Iterator& p, const elem& e){
	node* x = p.v;
	node* toad = new node();
	toad->val = e;
	toad->prev = x->prev;
	toad->next = x;
	(x->prev)->next = x->prev = toad;
	n++;
}

template <typename elem>
void dlist<elem>::remove(const Iterator& p){
	node* x = p.v;
	node* u = x->prev;
	node* w = x->next;
	u->next = w;
	w->prev = u;
	delete x;
	n--;
}

template <typename elem>
void dlist<elem>::insertionSort(){
	if (empty()){
		return;
	}
	Iterator i= ++begin();
	while( i!= end()){
		Iterator j = i;
		--j;
		while ( j != --begin() && (*j > *i)){
			--j;
		}
		Iterator p = j;
		++p;
		add(p,*i);
		Iterator temp= i;
		++temp;
		remove(i);
		i = temp;
	}
}

template <typename elem>
void dlist<elem>::remove_duplicates_sorted() {
	if (empty()) {
		return;
	}
	Iterator i = begin();
	Iterator j = i;
	while(i != --end()){
        j = i;
        ++j;
		if (*i == *j){
			remove(j);
		}
		else {
			++i;
		}
	}
}

template <typename elem>
typename dlist<elem>::Iterator dlist<elem>::begin() {
	return Iterator(header->next);
}

template <typename elem>
typename dlist<elem>::Iterator dlist<elem>::end() {
	return Iterator(trailer);
}

template <typename elem>
dlist<elem>::Iterator::Iterator(node* u) : v(u) {}

template <typename elem>
elem& dlist<elem>::Iterator::operator*(){
	return (v->val);
}

template <typename elem>
typename dlist<elem>::Iterator& dlist<elem>::Iterator::operator--(){
	v =v ->prev;
	return *this;
}

template <typename elem>
typename dlist<elem>::Iterator& dlist<elem>::Iterator::operator++(){
	v = v->next;
	return *this;
}

template <typename elem>
bool dlist<elem>::Iterator::operator==(const Iterator& p) const{
	return (v == p.v);
}

template <typename elem>
bool dlist<elem>::Iterator::operator!=(const Iterator& p) const{
	return (v!=p.v);
}


template <typename elem>
class linktree{
public:
	class tnode{
	public:
		elem val;
		tnode* left;
		tnode* right;
		tnode(const elem& v_val, tnode* v_left = NULL, tnode* v_right = NULL): val(v_val), left(v_left), right(v_right) {}
	};
public:
	tnode* root;
public:
	linktree(): root(NULL) {}
	void insert(const elem& e, tnode*& v);
	void print(tnode* v) const;
	int height(tnode* v) const;
	void maketree(dlist<elem>& l, bool remove_duplicates);
	void func_maketree(dlist<elem>& l, int start, int end, tnode*& v);
	bool isBst(tnode* v) const;
	bool func_isBst(tnode* v, int min, int max) const;
	bool swapValue(const elem& e1, const elem& e2);
	tnode* searchtree(tnode* v,const elem& e) const;
	tnode* searchbst(tnode* v,const elem& e) const;

};

template <typename elem>
void linktree<elem>::insert (const elem& e, tnode*& v){
	if (v == NULL){
		v = new tnode(e);
	}
	else if (e < v->val){
		insert(e, v->left);
	}
	else if (e > v->val) {
		insert(e, v->right);
	}
}

template <typename elem>
void linktree<elem>::print(tnode* v) const{
	if (v != NULL){
	print(v->left);
	cout<<v->val<<" ";
	print(v->right);
	}
}

template <typename elem>
int linktree<elem>::height(tnode* v) const{
	if (v == NULL){
		return -1;
	}
	int leftheight = height(v->left);
	int rightheight = height(v->right);
	int max = (leftheight >= rightheight) ? leftheight : rightheight;
	return max + 1;
}

template <typename elem>
void linktree<elem>::maketree(dlist<elem>& l, bool remove_duplicates){
	if (remove_duplicates){
    		l.remove_duplicates_sorted();
	}
	func_maketree(l, 0, l.size()-1, root);
}

template <typename elem>
void linktree<elem>::func_maketree(dlist<elem>& l, int start, int end, tnode*& v){

	if (start <= end) {
		int mid = (start+end)/2;
		typename dlist<elem>::Iterator p = l.begin();
		for (int i= 0; i < mid; ++i) {
			++p;
		}
		v = new tnode(*p);
		func_maketree(l,start,mid-1, v->left);
		func_maketree(l,mid+1,end, v->right);
	}
}

template <typename elem>
bool linktree<elem>::isBst(tnode* v) const {
	return func_isBst(v, INT_MIN, INT_MAX);
}

template <typename elem>
bool linktree<elem>::func_isBst(tnode* v, int min, int max) const {
	if (v== NULL) {
		return true;
	}
	if ((v->val > min && v->val < max)  && func_isBst(v->left, min, v->val) && func_isBst(v->right, v->val, max)) {
		return true;
	}
	else {
		return false;
	}

}

template <typename elem>
typename linktree<elem>::tnode* linktree<elem>::searchbst(tnode* v, const elem& e) const {

	if (v == NULL){
		return NULL;
	}
	if (v->val == e) {
		return v;
	}
	else if (e < v->val) {
		return searchbst(v->left, e);
	}
	else if (e > v->val) {
		return searchbst(v->right, e);
	}
}

template <typename elem>
typename linktree<elem>::tnode* linktree<elem>::searchtree(tnode* v, const elem& e) const {

	if (v == NULL){
		return NULL;
	}
	if (v->val == e) {
		return v;
	}
	else if (searchtree(v->left, e) != NULL) {
		return searchtree(v->left, e);
	}
	else if (searchtree(v->right, e) != NULL) {
		return searchtree(v->right, e);
	}
	return NULL;
}

template <typename elem>
bool linktree<elem>::swapValue(const elem& e1, const elem& e2) {
	tnode* p1 = searchtree(root, e1);
	tnode* p2 = searchtree(root, e2);
	if (p1 != NULL && p2!= NULL){
		elem temp;
		temp = p1->val;
		p1->val = p2->val;
		p2->val = temp;
		return true;
	}
	return false;
}

int main(){
	dlist<int> input_list;
	ifstream input;
	input.open("input4-single.txt",ios::in);
	int temp;
	int n=0;
	while(input>>temp){
		input_list.addback(temp);
		n++;
	}
	cout<<"Input Sequence"<<endl;
	for (dlist<int>::Iterator i = input_list.begin(); i != input_list.end(); ++i) {
		cout<<*i<<" ";
	}
	cout<<endl;
	
	int do_sort;
	cout<<"Do you want to sort the list"<<endl;
	cout<<"1: Yes \t0: No"<<endl;
	cin>>do_sort;
	linktree<int> input_tree;
	if (do_sort){
		input_list.insertionSort();
		cout<<"Sorted Sequence"<<endl;
		for (dlist<int>::Iterator i = input_list.begin(); i != input_list.end(); ++i) {
			cout<<*i<<" ";
		}
		cout<<endl;
		
		input_tree.maketree(input_list, true);
	}
	else {
		input_tree.maketree(input_list, false);
	}


	
	cout<<"Constructed Binary Tree (inorder)"<<endl;
	input_tree.print(input_tree.root);
	cout<<endl;


	int do_swap = 1;

	while(do_swap) {
		cout<<"Do you want to swap the elements in the binary tree?"<<endl;
		cout<<"1: Yes \t0: No"<<endl;
		cin>>do_swap;
		if (do_swap){
			int e1, e2;
			cout<<"Enter the first element:"<<endl;
			cin>>e1;
			cout<<"Enter the second element:"<<endl;
			cin>>e2;
			if (input_tree.swapValue(e1,e2)){
				cout<<"New Binary Tree (inorder)"<<endl;
				input_tree.print(input_tree.root);
				cout<<endl;
			}
			else {
				cout<<"Element(s) not found"<<endl;
			}
		}
	}


	cout<<"Height of binary tree: "<<input_tree.height(input_tree.root)<<endl;
	if (input_tree.isBst(input_tree.root)) {
		cout<<"True, it is a BST"<<endl;
	}
	else {
		cout<<"False, it is not a BST"<<endl;
	}

	input.close();
	return 0;
}
