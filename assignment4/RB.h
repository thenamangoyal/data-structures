#ifndef RB_H
#define RB_H

#include <iostream>
#include <iomanip>
#include <string>

enum Color {RED, BLACK};

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
class rbtree{
public:
	typedef typename E::Key K;
	typedef typename E::Value V;
public:
	class node{
	public:
		E elem;
		bool color;
		node* left;
		node* right;
		node* parent;
		node(const E& v_elem = E(), bool v_color = RED, node* v_left = NULL, node* v_right = NULL, node* v_parent = NULL): elem(v_elem), color(v_color), left(v_left), right(v_right), parent(v_parent) {}
	};

private:
	node* root;
	node* nil;
	int n;

public:
	class Iterator{
	private:
		node* v;
		rbtree& ptree;
	public:
		Iterator(node* u, rbtree& tree) : v(u), ptree(tree) {}
		Iterator(const Iterator& p): v(p.v), ptree(p.ptree) {}
		const E& operator*() {return v->elem;}
		Iterator& operator=(const Iterator& p){
			if (this != &p){
				v = p.v;
				ptree = p.ptree;
			}
			return *this;
		}
		bool operator==(const Iterator& i) const{ return v == i.v;}
		Iterator& operator++();
		Iterator& operator--();
		friend class rbtree<E>;
	};

private:
	node* minimum(node* x);
	node* search(node* x, const K& k);
	void leftrotate(node* x);
	void rightrotate(node* x);
	void fixinsert(node* z);
	void transplant(node* u, node* v);
	void fixremove(node* x);
	int max(int a, int b);

	void genPrintMatrix(node* curr, int depth, int& counter, node*** printMatrix);

	int height(node* curr);
	int blackheight(node* curr);
	int countleaf(node* curr);
	int countnodes(node* curr);	
	void keyinrange(node* curr, const K& a, const K& b);

	void print_old(node* p,int indent=0);
	
public:
	rbtree() {
		nil = new node(0,BLACK);
		nil->color = BLACK;
		root = nil;
		n = 0;
	}
	int size() const {return n;}
	void empty() const {return (n==0);}

	Iterator begin();
	Iterator end();

	Iterator insert(const K& k, const V& v);
	void remove(const K& k);
	void remove(const Iterator& p);
	Iterator find(const K& k);

	int getheight();
	int getblackheight();
	int getcountleaf();
	int getcountnodes();
	void getkeyinrange(const K& a, const K& b);


	void print();
	void print_rot();

};



///////////////////////////////////////////////
////////////////// Iterator ///////////////////
///////////////////////////////////////////////

template <typename E>
typename rbtree<E>::Iterator& rbtree<E>::Iterator::operator++(){
	node* succ = nil;
	if (v == nil){
		return *this;
	}
	if (v->right){
		succ = v->right;
		while(succ->left){
			succ = succ->left;
		}
	}
	else {
		succ = nil;
		node* ancestor = ptree.root;

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
typename rbtree<E>::Iterator& rbtree<E>::Iterator::operator--(){
	node* pred = nil;
	if (v == nil){
		return *this;
	}
	if (v->left){
		pred = v->left;
		while(pred->right){
			pred = pred->right;
		}
	}
	else {
		pred = nil;
		node* ancestor = ptree.root;

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

template <typename E>
typename rbtree<E>::Iterator rbtree<E>::begin(){
	if (root == nil){
		return Iterator(nil, *this);
	}
	node* smallest = root;
	while(smallest->left){
		smallest = smallest->left;
	}
	return Iterator(smallest, *this);
}


template <typename E>
typename rbtree<E>::Iterator rbtree<E>::end(){
	return Iterator(nil, *this);
}

template <typename E>
int rbtree<E>::countnodes(node* curr){
	if (curr){
		return (countnodes(curr->left) + countnodes(curr->right) + 1);
	}
	return 0;
}


template <typename E>
void rbtree<E>::genPrintMatrix(node* curr, int depth, int& counter, node*** printMatrix){
	if (curr != nil){

		genPrintMatrix(curr->left, depth+1, counter, printMatrix);
		printMatrix[depth][counter] = curr;
		counter++;
		genPrintMatrix(curr->right, depth+1, counter, printMatrix);
	}
	
}


template <typename E>
void rbtree<E>::print(){
	int high = height(root);
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
		        if (p->color){
		        	std::cout<<"[B]";
		        }
		        else{
		        	std::cout<<"[R]";
		        }
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
void rbtree<E>::print_rot(){
	print_old(root);
}

template <typename E>
void rbtree<E>::print_old(node* p,int indent){
	
	if(p != nil) {
        if(p->right != nil) {
            print_old(p->right, indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right != nil) {std::cout<<" /\n" << std::setw(indent) << ' ';}
        std::cout<< p->elem.key();
        if (p->color){
        	std::cout<<"[B]"<<std::endl;
        }
        else{
        	std::cout<<"[R]"<<std::endl;
        }
        if(p->left != nil) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            print_old(p->left, indent+4);
        }
    }
          
}

template <typename E>
typename rbtree<E>::node* rbtree<E>::minimum(node* x){
	while (x->left != nil){
		x = x->left;
	}
	return x;
}

template <typename E>
int rbtree<E>::max(int a, int b){
	return (a>b) ? a : b;
}

template <typename E>
void rbtree<E>::leftrotate(node* x){
	node* y = x->right;
	x->right = y->left;
	if (y->left != nil){
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nil){
		root = y;
	}
	else if (x == x->parent->left){
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

template <typename E>
void rbtree<E>::rightrotate(node* x){
	node* y = x->left;
	x->left = y->right;
	if (y->right != nil){
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nil){
		root = y;
	}
	else if (x == x->parent->right){
		x->parent->right = y;
	}
	else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

template <typename E>
int rbtree<E>::height(node* curr){
	if (curr == nil){
		return 0;
	}
	int lh = height(curr->left);
	int rh = height(curr->right);
	return (1 + max(lh, rh));
}

template <typename E>
int rbtree<E>::blackheight(node* curr){
	if (curr == nil){
		return 0;
	}
	int lh = blackheight(curr->left);
	int rh = blackheight(curr->right);
	if (curr->color == RED){
		return max(lh, rh);
	}
	return (1 + max(lh, rh));
}

template <typename E>
int rbtree<E>::countleaf(node* curr){
	if (curr == nil){
		return 0;
	}
	if (curr->left == nil && curr->right == nil){
		return 1;
	}
	return (countleaf(curr->left) + countleaf(curr->right));
}

template <typename E>
void rbtree<E>::keyinrange(node* curr, const K& a, const K& b){
	if (curr != nil){
		if (a < curr->elem.key()){
			keyinrange(curr->left, a, b);			
		}
		if (curr->elem.key() >= a && curr->elem.key() <= b){
			std::cout<<curr->elem.key()<<" ";
		}
		if (b > curr->elem.key()){
			keyinrange(curr->right, a, b);
		}		
	}
}

template <typename E>
int rbtree<E>::getheight(){
	return height(root);
}

template <typename E>
int rbtree<E>::getblackheight(){
	return blackheight(root);
}

template <typename E>
int rbtree<E>::getcountleaf(){
	return countleaf(root);
}

template <typename E>
int rbtree<E>::getcountnodes(){
	return countnodes(root);
}

template <typename E>
void rbtree<E>::getkeyinrange(const K& a, const K& b){
	getkeyinrange(root, a, b);
}

template <typename E>
typename rbtree<E>::Iterator rbtree<E>::insert(const K& k, const V& v){
	node* z = new node(Entry<K,V>(k,v));
	node* y = nil;
	node* x = root;
	
	while (x != nil){
		y = x;
		if (z->elem.key() < x->elem.key()){
			x = x->left;
		}
		else if (z->elem.key() > x->elem.key()) {
			x = x->right;
		}
		else {
			x->elem.setvalue(v);
			return find(k);
		}
	}
	z->parent = y;
	if (y == nil){
		root = z;
	}
	else if (z->elem.key() < y->elem.key()){
		y->left = z;
	}
	else {
		y->right = z;
	}
	z->left = nil;
	z->right = nil;
	z->color = RED;
	fixinsert(z);	
	n++;
	return find(k);
}

template <typename E>
void rbtree<E>::fixinsert(node* z){
	while(z->parent->color == RED){
		if (z->parent == z->parent->parent->left){			
			node* y = z->parent->parent->right;
			if (y->color == RED){				
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}			
			else{
				if (z == z->parent->right){				
					z = z->parent;
					leftrotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rightrotate(z->parent->parent);
			} 		
			
		}
		else{
			node* y = z->parent->parent->left;
			if (y->color == RED){
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else{
				if (z == z->parent->left){
					z = z->parent;
					rightrotate(z);
				}
			z->parent->color = BLACK;
			z->parent->parent->color = RED;
			leftrotate(z->parent->parent);
			}			
		}
	}
	root->color = BLACK;
}

template <typename E>
typename rbtree<E>::node* rbtree<E>::search(node* x, const K& k){
	while (x != nil && k != x->elem.key()){
		if (k < x->elem.key()){
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	return x;
}

template <typename E>
void rbtree<E>::transplant(node* u, node* v){
	if (u->parent == nil){
		root = v;
	}
	else if (u == u->parent->left){
		u->parent->left = v;
	}
	else{
		u->parent->right = v;
	}
	v->parent = u->parent;
}

template <typename E>
void rbtree<E>::remove(const K& k){
	node* z = search(root, k);
	if (z == nil){
		return;
	}
	node* y = z;
	node* x;
	bool y_ori_color = y->color;
	if (z->left == nil){
		x = z->right;
		transplant(z,z->right);
	}
	else if (z->right == nil){
		x = z->left;
		transplant(z,z->left);
	}
	else {
		y = minimum(z->right);
		y_ori_color = y->color;
		x = y->right;
		if (y->parent == z){
			x->parent = y;
		}
		else {
			transplant(y,y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z,y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (y_ori_color == BLACK){
		fixremove(x);
	}
	n--;
}

template <typename E>
void rbtree<E>::fixremove(node* x){
	while (x != root && x->color == BLACK){
		if (x == x->parent->left){
			node* w = x->parent->right;
			if (w->color == RED){
				w->color = BLACK;
				x->parent->color = RED;
				leftrotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK){
				w->color = RED;
				x = x->parent;
			}
			else{
				if (w->right->color == BLACK){
					w->left->color == BLACK;
					w->color = RED;
					rightrotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				leftrotate(x->parent);
				x = root;
			}
		}
		else {
			node* w = x->parent->left;
			if (w->color == RED){
				w->color = BLACK;
				x->parent->color = RED;
				rightrotate(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK){
				w->color = RED;
				x = x->parent;
			}
			else{
				if (w->left->color == BLACK){
					w->right->color == BLACK;
					w->color = RED;
					leftrotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rightrotate(x->parent);
				x = root;
			}

		}
	}
	x->color = BLACK;

}


template <typename E>
void rbtree<E>::remove(const Iterator& p){
	if (p == end()){
		// Not found		
		return;
	}
	node* u = p.v;
	K k = u->elem.key();	
	remove(k);
}


template <typename E>
typename rbtree<E>::Iterator rbtree<E>::find(const K& k){
	return Iterator(search(root,k), *this);
}

#endif