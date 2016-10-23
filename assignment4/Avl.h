#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <iomanip>

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
		node(const E& v_elem = E(), node* v_left = NULL, node* v_right = NULL, int v_height = 0): elem(v_elem), left(v_left), right(v_right), height(v_height) {}
	};
private:
	node* root;

private:
	void insert(node*& curr,const K& k, const V& v);
	void remove(node*& curr, const K& k);
	node* search(node* curr, const K& k);
	node* insucc(node* curr, const K& k);
	node* inpred(node* curr, const K& k);

	void print_old(node* p,int indent=0);
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
		const E& operator*() {return v->elem;}
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
	void print_rot();

};

template <typename E>
void AVL<E>::print_old(node* p,int indent){
	
	if(p != NULL) {
        if(p->right) {
            print_old(p->right, indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
        std::cout<<"("<< (p->elem).key()<<"," << p->elem.value()<<","<<p->height<<")"<<std::endl;
        if(p->left) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            print_old(p->left, indent+4);
        }
    }
          
}

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
			remove(curr->right,curr->elem.key());
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
		return -1;
	}
	return u->height;
}

template <typename E>
int AVL<E>::calcheight(node* u){
	if (u == NULL){
		return -1;
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
	
	print(); std::cout<<std::endl;
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
	print(); std::cout<<std::endl;
}

template <typename E>
void AVL<E>::print(){
	int high = calcheight(root)+1;
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
				std::cout << std::setw(4) << ' ';
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
void AVL<E>::print_rot(){
	print_old(root);
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




#endif

