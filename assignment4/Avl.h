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
public:
	node* root;


public:
	node* insert(node* curr,const K& k, const V& v);
	node* remove(node* curr, const K& k);
	node* search(node* curr, const K& k);
	node* insucc(node* curr, const K& k);
	node* inpred(node* curr, const K& k);
	void print(node* p,int indent=0);
private:
	int getbalance(node* u);
	node* leftrotate(node* u);
	node* rightrotate(node* u);
private:
	int height(node* u);
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

};

template <typename E>
void AVL<E>::print(node* p,int indent){
	
	if(p != NULL) {
        if(p->right) {
            print(p->right, indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
        std::cout<<"("<< (p->elem).key()<<"," << p->elem.value()<<","<<p->height<<")"<<std::endl;
        if(p->left) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            print(p->left, indent+4);
        }
    }
          
}

template <typename E>
int AVL<E>::getbalance(node* u) {
	return height(u->left) - height(u->right);
}

template <typename E>
typename AVL<E>::node* AVL<E>::insert(node* curr, const K& k, const V& v){
	if (curr == NULL){
		curr =  new node(Entry<K,V>(k,v));
		return curr;
	}
	else if (k < curr->elem.key()){
		curr->left = insert(curr->left,k,v);
	}
	else if (k > curr->elem.key()){
		curr->right = insert(curr->right,k,v);
	}
	else{
		curr->elem.setvalue(v);
		return curr;
	}
	curr->height = 1+ max(height(curr->left),height(curr->right));

	int bal = getbalance(curr);

	if(bal > 1 && k < curr->left->elem.key()){
		return rightrotate(curr);
	}
	if (bal>1 && k > curr->left->elem.key()){
		curr->left = leftrotate(curr->left);
		return rightrotate(curr);
	}
	if (bal<-1 && k > curr->right->elem.key()){
		return leftrotate(curr);
	}
	if (bal<-1 && k < curr->right->elem.key()){
		curr->right = rightrotate(curr->right);
		return leftrotate(curr);
	}

	return curr;
}

template <typename E>
typename AVL<E>::node* AVL<E>::remove(node* curr, const K& k){
	if (curr == NULL){
		return NULL;
	}
	else if (k < curr->elem.key()){
		curr->left = remove(curr->left,k);
	}
	else if (k > curr->elem.key()){
		curr->right = remove(curr->right,k);
	}
	else{
		if (curr->left == NULL && curr->right == NULL){
			delete curr;
			return NULL;
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
			curr->right = remove(curr->right,curr->elem.key());
		}
	}
	curr->height = 1+ max(height(curr->left),height(curr->right));

	int bal = getbalance(curr);

	if(bal > 1 && getbalance(curr->left)>=0){
		return rightrotate(curr);
	}
	if (bal>1 && getbalance(curr->left)<0){
		curr->left = leftrotate(curr->left);
		return rightrotate(curr);
	}
	if (bal<-1 && getbalance(curr->right)<=0){
		return leftrotate(curr);
	}
	if (bal<-1 && getbalance(curr->right)>0){
		curr->right = rightrotate(curr->right);
		return leftrotate(curr);
	}

	return curr;
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
typename AVL<E>::node* AVL<E>::leftrotate(node* u) {
	node* v = u->right;	
	node* T2 = v->left;

	v->left = u;
	u->right = T2;

	u->height = 1 + max(height(u->left), height(u->right));
	v->height = 1 + max(height(v->left), height(v->left));
	return v;

}

template <typename E>
typename AVL<E>::node* AVL<E>::rightrotate(node* u) {	

	node* v = u->left;
	node* T2 = v->right;

	v->right = u;
	u->left = T2;

	u->height = 1 + max(height(u->left), height(u->right));
	v->height = 1 + max(height(v->left), height(v->left));

	return v;

}

template <typename E>
int AVL<E>::height(node* u) {
	if (u == NULL){
		return -1;
	}	
	return u->height;
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
	return Iterator(insert(root,k,v), *this);
}

template <typename E>
void AVL<E>::erase(const K& k){
	if (search(root,k) ==  NULL){
		// Not found
		return;
	}
	root = remove(root,k);
}

template <typename E>
void AVL<E>::erase(const Iterator& p){
	if (p == end()){
		// Not found
		return;
	}
	root = remove(root, (*p).key());
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

