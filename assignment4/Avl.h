#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <iomanip>
#include <string>


template <typename elem>
class slist;

template <typename elem>
class linkstack;

template <typename K, typename V>
class Entry{
public:
	typedef K Key;
	typedef V Value;
private:
	K _key;
	V _value;
public:
	Entry(const K& k = K(), const V& v = V()): _key(k), _value(v) {}
	const K& key() const {return _key;}
	const V& value() const {return _value;}
	void setKey(const K& k) {_key = k;}
	void setvalue(const V& v) {_value = v;}
};


template <typename E>
class AVL{
public:
	typedef typename E::Key K;
	typedef typename E::Value V;
private:
	class node{
	public:
		E elem;
		node* left;
		node* right;
		int height;
	public:
		node(const E& v_elem = E(), node* v_left = NULL, node* v_right = NULL, int v_height = 1): elem(v_elem), left(v_left), right(v_right), height(v_height) {}
		node& operator=(const node& n){
			if (this != &n){
				elem = n.elem;
				left = n.left;
				right = n.right;
				height = n.height;
			}
			return *this;
		}
	};
private:
	node* root;

private:
	void insert(node*& curr,const K& k, const V& v);
	void remove(node*& curr, const K& k);
	node* search(node* curr, const K& k);
	node* insucc(node* curr, const K& k);
	node* inpred(node* curr, const K& k);

	void genPrintMatrix(node* curr, int depth, int& counter, node*** printMatrix);

	int getbalance(node* u);
	void leftrotate(node*& u);
	void rightrotate(node*& u);

	int height(node* u);
	int calcheight(node* u);
	void getmaxwidth(node* curr, int level, int* count);
	int width(node* curr);
	int countnodes(node* curr);
	int max(int a, int b);

private:
	int n;
public:
	class Iterator{
	private:
		node* v;
		AVL& parent;
	public:
		Iterator(node* u, AVL& tree) : v(u), parent(tree) {}
		Iterator(const Iterator& p): v(p.v), parent(p.parent) {}
		const E& operator*() {return v->elem;}
		Iterator& operator=(const Iterator& p){
			if (this != &p){
				v = p.v;
				parent = p.parent;
			}
			return *this;
		}
		bool operator==(const Iterator& i) const{ return v == i.v;}
		Iterator& operator++();
		Iterator& operator--();
		friend class AVL<E>;
	};
	
public:
	AVL(): root(NULL), n(0) {}
	int size() const {return n;}
	bool empty() const {return n==0;}
	Iterator begin();
	Iterator end();
	Iterator firstEntry();
	Iterator lastEntry();
	Iterator ceilingEntry(const K& k);
	Iterator floorEntry(const K& k);
	Iterator lowerEntry(const K& k);
	Iterator higherEntry(const K& k);
	Iterator find(const K& k);
	Iterator put(const K& k, const V& v);
	void erase(const K& k);
	void erase(const Iterator& p);
	void print();
	bool targetsum(const K& sum);

};

template <typename E>
void AVL<E>::genPrintMatrix(node* curr, int depth, int& counter, node*** printMatrix){
	if (curr){

		genPrintMatrix(curr->left, depth+1, counter, printMatrix);
		printMatrix[depth][counter] = curr;
		counter++;
		genPrintMatrix(curr->right, depth+1, counter, printMatrix);
	}
	
}


template <typename E>
int AVL<E>::getbalance(node* u) {
	return height(u->left) - height(u->right);
}

template <typename E>
void AVL<E>::insert(node*& curr, const K& k, const V& v){
	if (curr == NULL){
		curr =  new node(Entry<K,V>(k,v));
		return;
	}
	else if (k < curr->elem.key()){
		insert(curr->left,k,v);
	}
	else if (k > curr->elem.key()){
		insert(curr->right,k,v);
	}
	else{
		curr->elem.setvalue(v);
		return;
	}
	curr->height = 1+ max(height(curr->left),height(curr->right));

	int bal = getbalance(curr);

	if(bal > 1 && k < curr->left->elem.key()){
		rightrotate(curr);
		return;
	}
	if (bal>1 && k > curr->left->elem.key()){
		leftrotate(curr->left);
		rightrotate(curr);
		return;
	}
	if (bal<-1 && k > curr->right->elem.key()){
		leftrotate(curr);
		return;
	}
	if (bal<-1 && k < curr->right->elem.key()){
		rightrotate(curr->right);
		leftrotate(curr);
		return;
	}

	return;
}

template <typename E>
void AVL<E>::remove(node*& curr, const K& k){
	if (curr == NULL){
		return;
	}
	else if (k < curr->elem.key()){
		remove(curr->left,k);
	}
	else if (k > curr->elem.key()){
		remove(curr->right,k);
	}
	else{
		if (curr->left == NULL && curr->right == NULL){
			node* temp = curr;
			curr = NULL;
			delete temp;			
			return;
		}
		else if (curr->right == NULL){
			node* temp = curr;
			curr= curr->left;
			delete temp;
		}
		else if (curr->left == NULL){
			node* temp = curr;
			curr= curr->right;
			delete temp;
		}
		else{
			node* insucc = curr->right;
			while(insucc->left){
				insucc = insucc->left;
			}
			curr->elem = insucc->elem;
			remove(curr->right,insucc->elem.key());
		}
	}
	curr->height = 1+ max(height(curr->left),height(curr->right));

	int bal = getbalance(curr);

	if(bal > 1 && getbalance(curr->left)>=0){
		rightrotate(curr);
		return;
	}
	if (bal>1 && getbalance(curr->left)<0){
		leftrotate(curr->left);
		rightrotate(curr);
		return;
	}
	if (bal<-1 && getbalance(curr->right)<=0){
		leftrotate(curr);
		return;
	}
	if (bal<-1 && getbalance(curr->right)>0){
		rightrotate(curr->right);
		leftrotate(curr);
		return;
	}

	return;
}

template <typename E>
typename AVL<E>::node* AVL<E>::search(node* curr, const K& k){
	if (curr == NULL || k == curr->elem.key()){
		return curr;
	}
	if (k < curr->elem.key()){
		return search(curr->left, k);
	}
	if (k > curr->elem.key()){
		return search(curr->right, k);
	}

}

template <typename E>
typename AVL<E>::node* AVL<E>::insucc(node* curr, const K& k){
	node* v = search(root, k);
	if (v == NULL){
		return NULL;
	}
	node* succ = NULL;
	
	if (v->right){
		succ = v->right;
		while(succ->left){
			succ = succ->left;
		}
	}
	else {
		succ = NULL;
		node* ancestor = root;

		while (ancestor != v){
			if (v->elem.key() < ancestor->elem.key()){
				succ = ancestor;
				ancestor = ancestor->left;
			}
			else{
				ancestor = ancestor->right;
			}
		}
	}
	return succ;
}

template <typename E>
typename AVL<E>::node* AVL<E>::inpred(node* curr, const K& k){
	node* v = search(curr, k);
	if (v == NULL){
		return NULL;
	}
	node* pred = NULL;
	
	if (v->left){
		pred = v->left;
		while(pred->right){
			pred = pred->right;
		}
	}
	else {
		pred = NULL;
		node* ancestor = root;

		while (ancestor != v){
			if (v->elem.key() > ancestor->elem.key()){
				pred = ancestor;
				ancestor = ancestor->right;
			}
			else{
				ancestor = ancestor->left;
			}
		}
	}
	
	return pred;
}

template <typename E>
void AVL<E>::leftrotate(node*& u) {

	K k = u->elem.key();
	std::cout<<":: Left rotating at key "<<k<<std::endl;
	std::cout<<"------ Before rotation"<<std::endl;
	print(); std::cout<<std::endl;

	node* v = u->right;	
	node* T2 = v->left;

	v->left = u;
	u->right = T2;

	u->height = 1 + max(height(u->left), height(u->right));
	v->height = 1 + max(height(v->left), height(v->left));
	
	u = v;
	std::cout<<"------ After rotation"<<std::endl;
	print(); std::cout<<std::endl;

}

template <typename E>
void AVL<E>::rightrotate(node*& u) {

	K k = u->elem.key();
	std::cout<<":: Right rotating at key "<<k<<std::endl;
	std::cout<<"------ Before rotation"<<std::endl;
	print(); std::cout<<std::endl;

	node* v = u->left;
	node* T2 = v->right;

	v->right = u;
	u->left = T2;

	u->height = 1 + max(height(u->left), height(u->right));
	v->height = 1 + max(height(v->left), height(v->left));	

	u = v;
	std::cout<<"------ After rotation"<<std::endl;
	print(); std::cout<<std::endl;

}

template <typename E>
int AVL<E>::height(node* u) {
	if (u == NULL){
		return 0;
	}
	return u->height;
}

template <typename E>
int AVL<E>::calcheight(node* u){
	if (u == NULL){
		return 0;
	}
	int lh = calcheight(u->left);
	int rh = calcheight(u->right);
	return (1 + max(lh,rh));
}

template <typename E>
void AVL<E>::getmaxwidth(node* curr, int level, int* count){
	if (curr){
		count[level]++;
		getmaxwidth(curr->left,level+1, count);
		getmaxwidth(curr->right, level+1, count);
	}
}

template <typename E>
int AVL<E>::width(node* curr){
	if (curr){
		int* count = new int[height(curr)+1];
		int level=0;
		getmaxwidth(curr, level, count);
		int width = count[0];
		for(int i=1; i< height(curr)+1; i++){
			if (width < count[i]){
				width = count[i];
			}
		}
		delete [] count;
		return width;
	}
	return 0;
	
}

template <typename E>
int AVL<E>::countnodes(node* curr){
	if (curr){
		return (countnodes(curr->left) + countnodes(curr->right) + 1);
	}
	return 0;
}

template <typename E>
int AVL<E>::max(int a, int b) {
	return (a>b)? a: b;
}


///////////////////////////////////////////////
////////////// Public Interface ///////////////
///////////////////////////////////////////////

template <typename E>
typename AVL<E>::Iterator AVL<E>::begin(){
	if (root == NULL){
		return Iterator(NULL, *this);
	}
	node* smallest = root;
	while(smallest->left){
		smallest = smallest->left;
	}
	return Iterator(smallest, *this);
}

template <typename E>
typename AVL<E>::Iterator AVL<E>::end(){
	return Iterator(NULL, *this);
}

template <typename E>
typename AVL<E>::Iterator AVL<E>::firstEntry(){
	return begin();
}

template <typename E>
typename AVL<E>::Iterator AVL<E>::lastEntry(){
	if (root == NULL){
		return Iterator(NULL, *this);
	}
	node* largest = root;
	while (largest->right){
		largest = largest->right;
	}
	return Iterator(largest, *this);
}

template <typename E>
typename AVL<E>::Iterator AVL<E>::ceilingEntry(const K& k){
	
	node* succ = NULL;
	node* curr = root;
	while(curr){
		
		if (k < curr->elem.key()){
			succ = curr;
			curr = curr->left;
		}
		else if (k > curr->elem.key()) {
			
			curr = curr->right;
		}
		else {
			succ = curr;	
			break;
		}
	}
	return Iterator(succ, *this);
}

template <typename E>
typename AVL<E>::Iterator AVL<E>::floorEntry(const K& k){
	node* prev = NULL;	
	node* curr = root;
	while(curr){
		
		if (k < curr->elem.key()){			
			curr = curr->left;
		}
		else if (k > curr->elem.key()) {
			prev = curr;
			curr = curr->right;
		}
		else {
			prev = curr;	
			break;
		}
	}
	return Iterator(prev, *this);

}

template <typename E>
typename AVL<E>::Iterator AVL<E>::lowerEntry(const K& k){
	node* prev = NULL;	
	node* curr = root;
	while(curr){
		
		if (k < curr->elem.key()){			
			curr = curr->left;
		}
		else if (k > curr->elem.key()) {
			prev = curr;
			curr = curr->right;
		}
		else {
			if (curr->left){
				prev = curr->left;
				while(prev->right){
					prev = prev->right;
				}
			}
			break;
		}
	}
	return Iterator(prev, *this);
	
}

template <typename E>
typename AVL<E>::Iterator AVL<E>::higherEntry(const K& k){
	node* succ = NULL;
	node* curr = root;
	while(curr){
		
		if (k < curr->elem.key()){
			succ = curr;
			curr = curr->left;
		}
		else if (k > curr->elem.key()) {
			
			curr = curr->right;
		}
		else {
			if (curr->right){
				succ = curr->right;			
				while(succ->left){
					succ = succ->left;
				}
			}
			break;
		}
	}
	return Iterator(succ, *this);

}

template <typename E>
typename AVL<E>::Iterator AVL<E>::find(const K& k){
	return Iterator(search(root,k), *this);
}

template <typename E>
typename AVL<E>::Iterator AVL<E>::put(const K& k, const V& v){
	std::cout<<"Inserting entry with key "<<k<<" and value "<<v<<std::endl;
	if (search(root,k) == NULL){
		n++;
	}
	insert(root,k,v);
	std::cout<<"Tree after insertion of key "<<k<<std::endl;
	print();
	std::cout<<std::endl;

	
	return find(k);
}

template <typename E>
void AVL<E>::erase(const K& k){	
	std::cout<<"Deleting entry with key "<<k<<std::endl;
	if (search(root,k) ==  NULL){
		// Not found
		std::cout<<":: No entry found with key "<<k<<std::endl;
		return;
	}
	remove(root,k);
	n--;
	std::cout<<"Tree after deletion of key "<<k<<std::endl;
	print();
	std::cout<<std::endl;
}

template <typename E>
void AVL<E>::erase(const Iterator& p){
	std::cout<<"Deleting using iterator";
	if (p == end()){
		// Not found
		std::cout<<std::endl<<":: End iterator "<<std::endl;
		return;
	}
	node* u = p.v;
	K k = u->elem.key();
	std::cout<<" with key "<<k<<std::endl;
	remove(root, k);
	n--;
	std::cout<<"Tree after deletion using iterator with key "<<k<<std::endl;
	print();
	std::cout<<std::endl;
}

template <typename E>
void AVL<E>::print(){
	int high = calcheight(root);
	int wide = countnodes(root);
	node*** printMatrix = new node**[high];	
	for(int i=0; i< high; i++){
		printMatrix[i] = new node*[wide];
		for(int j=0; j< wide; j++){
			printMatrix[i][j] = NULL;
		}
	}
	int counter = 0;
	genPrintMatrix(root, 0, counter, printMatrix);

	for(int i=0; i< high; i++){
		for (int j=0; j < wide; j++){
			node* p = printMatrix[i][j];
			if (p == NULL){
				std::cout << std::setw(6) << ' ';
			}
			else {
				std::cout<<"("<< (p->elem).key()<<"," << p->elem.value()<<")";
			}
		}
		std::cout<<std::endl;
	}


	for(int i=0; i< high; i++){
		delete [] printMatrix[i];
	}
	delete [] printMatrix;
}

template <typename E>
bool AVL<E>::targetsum(const K& sum){
	linkstack<node*> stack1;
	linkstack<node*> stack2;
	
	bool finish1 = false;
	bool finish2 = false;

	node* curr1 = root;
	node* curr2 = root;

	K key1 = 0;
	K key2 = 0;

	V value1;
	V value2;



	while(1){
		while(finish1 == false){
			if (curr1 != NULL){
				stack1.push(curr1);
				curr1 = curr1->left;
			}
			else{
				if (stack1.empty()){
					finish1 = true;
				}
				else{
					curr1 = stack1.top(); stack1.pop();
					key1 = curr1->elem.key();
					value1 = curr1->elem.value();
					curr1 = curr1->right;
					finish1 = true;
				}
			}
		}

		while(finish2 == false){
			if (curr2 != NULL){
				stack2.push(curr2);
				curr2 = curr2->right;
			}
			else {
				if (stack2.empty()){
					finish2 = true;
				}
				else{
					curr2 = stack2.top(); stack2.pop();
					key2 = curr2->elem.key();
					value2 = curr2->elem.value();
					curr2 = curr2->left;
					finish2 = true;
				}
			}
		}

		if ( (key1 != key2) && (key1 + key2 == sum) ){
			std::cout<<"Found a pair matching target sum, entry1: ("<<key1<<","<<value1<<") entry2: ("<<key2<<","<<value2<<")"<<std::endl;
			return true;
		}
		else if ((key1 + key2 < sum)){
			finish1 = false;
		}
		else if ((key1 + key2 > sum)){
			finish2 = false;
		}

		if (key1 >= key2){
			std::cout<<"Couldn't find any pair matching target sum."<<std::endl;
			return false;
		}
	}


	
}


///////////////////////////////////////////////
////////////////// Iterator ///////////////////
///////////////////////////////////////////////

template <typename E>
typename AVL<E>::Iterator& AVL<E>::Iterator::operator++(){
	node* succ = NULL;
	if (v == NULL){
		return *this;
	}
	if (v->right){
		succ = v->right;
		while(succ->left){
			succ = succ->left;
		}
	}
	else {
		succ = NULL;
		node* ancestor = parent.root;

		while (ancestor != v){
			if (v->elem.key() < ancestor->elem.key()){
				succ = ancestor;
				ancestor = ancestor->left;
			}
			else{
				ancestor = ancestor->right;
			}
		}
	}
	v = succ;
	return *this;
}

template <typename E>
typename AVL<E>::Iterator& AVL<E>::Iterator::operator--(){
	node* pred = NULL;
	if (v == NULL){
		return *this;
	}
	if (v->left){
		pred = v->left;
		while(pred->right){
			pred = pred->right;
		}
	}
	else {
		pred = NULL;
		node* ancestor = parent.root;

		while (ancestor != v){
			if (v->elem.key() > ancestor->elem.key()){
				pred = ancestor;
				ancestor = ancestor->right;
			}
			else{
				ancestor = ancestor->left;
			}
		}
	}
	v = pred;
	return *this;
}


template <typename elem>
class slist {
	private:
	class slnode {
	public:
		elem val;
		slnode* next;
	};
public:
	slist();
	~slist();
	bool empty() const;
	void addfront(const elem& e);
	void removefront();
	const elem& front() const;
private:
	slnode* head;
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
	slnode* toadd = new slnode;
	toadd->val = e;
	toadd->next = head;
	head = toadd;
}

template <typename elem>
void slist<elem>::removefront() {
	slnode* torem = head;
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



#endif

