#include <iostream>
#include <iomanip>
using namespace std;

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

class node{
public:
	int data;
	bool color;
	node* left;
	node* right;
	node* parent;
	node(int v_data, bool v_color = RED, node* v_left = NULL, node* v_right = NULL, node* v_parent = NULL): data(v_data), color(v_color), left(v_left), right(v_right), parent(v_parent) {}
};

class rbtree{
public:
	node* root;
	node* nil;
private:
	node* minimum(node* x);
	void leftrotate(node* x);
	void rightrotate(node* x);
	void fixinsert(node* z);
	void transplant(node* u, node* v);
	void fixremove(node* x);
	
public:
	rbtree() {
		nil = new node(0,BLACK);
		nil->color = BLACK;
		root = nil;
	}
	void insert(const int& n);
	void remove(const int& n);

	node* search(node* x, const int& n);
	void print(node* p,int indent=0);

};


void rbtree::print(node* p,int indent){
	
	if(p != NULL) {
        if(p->right) {
            print(p->right, indent+4);
        }
        if (indent) {
            cout << setw(indent) << ' ';
        }
        if (p->right) {cout<<" /\n" << setw(indent) << ' ';}
        cout<< p->data;
        if (p->color){
        	cout<<"[B]"<<endl;
        }
        else{
        	cout<<"[R]"<<endl;
        }
        if(p->left) {
            cout << setw(indent) << ' ' <<" \\\n";
            print(p->left, indent+4);
        }
    }
          
}

node* rbtree::minimum(node* x){
	while (x->left != nil){
		x = x->left;
	}
	return x;
}

void rbtree::leftrotate(node* x){
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

void rbtree::rightrotate(node* x){
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


void rbtree::insert(const int& n){
	node* z = new node(n);
	node* y = nil;
	node* x = root;
	
	while (x != nil){
		y = x;
		if (z->data < x->data){
			x = x->left;
		}
		else if (z->data > x->data) {
			x = x->right;
		}
		else {
			x->data = z->data;
			return;
		}
	}
	z->parent = y;
	if (y == nil){
		root = z;
	}
	else if (z->data < y->data){
		y->left = z;
	}
	else {
		y->right = z;
	}
	z->left = nil;
	z->right = nil;
	z->color = RED;
	fixinsert(z);
}

void rbtree::fixinsert(node* z){
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

node* rbtree::search(node* x, const int& n){
	while (x != nil && n != x->data){
		if (n < x->data){
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	return x;
}

void rbtree::transplant(node* u, node* v){
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

void rbtree::remove(const int& n){
	node* z = search(root, n);
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
}

void rbtree::fixremove(node* x){
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

int main(){
	rbtree r;
	r.print(r.root);
	cout<<"New before"<<endl;
	r.insert(10);
	r.insert(20);
	r.insert(30);
	r.insert(15);
	r.print(r.root);
	cout<<"New after"<<endl;
	r.remove(10);
	r.remove(20);
	r.remove(30);
	r.remove(15);
	r.print(r.root);
	
	return 0;
}