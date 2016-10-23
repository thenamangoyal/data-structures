#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <iomanip>
#include <algorithm>

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
	class Iterator;
private:
	class node{
	public:
		E elem;
		node* left;
		node* right;
		node* p;
		int height;
	public:
		node(const E& v_elem = E(), node* v_left = NULL, node* v_right = NULL, node* v_p = NULL, int v_height = 0): elem(v_elem), left(v_left), right(v_right), p(v_p), height(v_height) {}
	};
public:
	class Iterator{
	private:
		node* v;
	public:
		Iterator(node* u) : v(u) {}
		E& operator*() {return v->elem;}
		bool operator==(const Iterator& i) const{ return v == i.v;}
		Iterator& operator++();
		Iterator& operator--();
		friend class AVL<E>;
	};
private:
	node* root;
	int n;
public:
	AVL(): root(NULL), n(0) {}
	int size() const {return n;}
	bool empty() const {return n==0;}
	//Iterator begin();
	//Iterator end();

public:
	Iterator insert(const K& k, const V& v);
	//void erase(const K& k);
	//void erase(const Iterator& i);
	void print(Iterator i,int indent=0);

private:
	int balance(node* u);
	void leftrotate(node* u);
	void rightrotate(node* u);

	void height(node* u);
};

template <typename E>
void AVL<E>::print(Iterator i,int indent){
	node* p = i.v;
	
	if(p != NULL) {
        if(p->right) {
            print(p->right, indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
        std::cout<<"("<< (p->elem).key()<<"," << p->elem.value()<<") "<<p->height<<std::endl;
        if(p->left) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            print(p->left, indent+4);
        }
    }
          
}

template <typename E>
int AVL<E>::balance(node* u) {
	return height(u->left) - height(u->right);
}

template <typename E>
typename AVL<E>::Iterator AVL<E>::insert(const K& k, const V& v){
	node* prev = NULL;
	node* curr = root;
	int newh = 0;
	while(curr){
		prev = curr;
		if (k< curr->elem.key()){
			curr = curr->left;
		}
		else if (k> curr->elem.key()) {
			curr = curr->right;
		}
		else {
			curr->elem.setvalue(v);
			return Iterator(curr);
		}
	}
	node* ins = new node (Entry<K,V>(k,v));
	ins->p = prev;
	if (prev ==  NULL){
		root = ins;
	}
	else if (k< prev->elem.key()){
		prev->left = ins;		
	}
	else {
		prev->right = ins;
	}
	return Iterator(ins);

	
}

template <typename E>
void AVL<E>::leftrotate(node* u) {
	node* v = u->left;
	node* T1 = v->left;
	node* T2 = v->right;
	node* T3 = u->right;

	v->right = u;
	u->left = T2;

	T2->p = u;
	v->p = u->p;
	u->p = v;

	u->height = 1 + max(height(u->left), height(u->right));
	v->height = 1 + max(height(v->left), height(v->left));

}

template <typename E>
void AVL<E>::rightrotate(node* u) {
	node* v = u->right;
	node* T1 = u->left;
	node* T2 = v->left;
	node* T3 = v->right;

	v->left = u;
	u->right = T2;

	T2->p = u;
	v->p = u->p;
	u->p = v;

	u->height = 1 + max(height(u->left), height(u->right));
	v->height = 1 + max(height(v->left), height(v->left));

}

template <typename E>
int AVL<E>::height(node* u) {
	if (u == NULL){
		return -1;
	}
	else {
		return u->height;
	}
}

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
	v = pred;
	return *this;
}




#endif

