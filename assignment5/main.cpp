#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

template <typename T>
class Graph {
private:
	class node{
	public:
		int dest;
		int border;
	public:
		node(int v_dest, int v_border = 0): dest(v_dest), border(v_border) {}
		node(const node& p): dest(p.dest), border(p.border) {}
	};
private:
	vector<T> Vertex;
	vector< list<node> > adj;


public:
	Graph();
	~Graph();
	int getIndex(const T& v);
	void addEdge(const T& t1, const T& t2, int border = 0);
	void print();

};

template <typename T>
Graph<T>::Graph() {
	
}

template <typename T>
Graph<T>::~Graph() {

}

template <typename T>
int Graph<T>::getIndex(const T& v){
	for (int i=0; i<Vertex.size() ; i++){
		if (v == Vertex[i]){
			return i;
		}
	}
	return -1;
}

template <typename T>
void Graph<T>::addEdge(const T& t1, const T& t2, int border) {
	int index1 = getIndex(t1);	

	if (index1 == -1){
		Vertex.push_back(t1);
		adj.push_back(list<node>());
		index1 = Vertex.size() -1;		
	}

	int index2 = getIndex(t2);

	if (index2 == -1){
		Vertex.push_back(t2);
		adj.push_back(list<node>());
		index2 = Vertex.size() -1;
	}

	typename list<node>::iterator itr;

	for (itr = adj[index1].begin(); itr != adj[index1].end(); ++itr){
		if (itr->dest == index2){
			itr->border = border;
			break;
		}
	}

	if (itr == adj[index1].end()){
		adj[index1].push_back(node(index2, border));
	}

	for (itr = adj[index2].begin(); itr != adj[index2].end(); ++itr){
		if (itr->dest == index1){
			itr->border = border;
			break;
		}
	}

	if (itr == adj[index2].end()){
		adj[index2].push_back(node(index1, border));
	}	

}

template <typename T>
void Graph<T>::print() {
	typename list<node>::iterator itr;
	for (int v =0; v < Vertex.size(); v++){
		cout<<"["<<Vertex[v]<<"]";
		for (itr = adj[v].begin(); itr != adj[v].end(); ++itr){
			cout<<" -> "<<Vertex[itr->dest];
		}
		cout<<endl;
	}
}

int main(){
	Graph<string> G;

	

	G.print();

/*
	ifstream input;
	input.open("countries.dat");

	string line;	

	while(getline(input,line)){
		
		stringstream input_stream(line);
	}*/

	

	return 0;
}