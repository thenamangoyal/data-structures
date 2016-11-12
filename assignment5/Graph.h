#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>

template <typename T>
class Graph {
private:
	class node{
	public:
		int dest;
		double border;
	public:
		node(int v_dest, double v_border = 0): dest(v_dest), border(v_border) {}
		node(const node& p): dest(p.dest), border(p.border) {}
	};
private:
	std::vector<T> Vertex;
	std::vector< std::list<node> > adj;

private:
	void list_n_dfs_visit(int u, bool* visited, int n);
	void border_n_dfs_visit(int u, bool* visited, int n);

public:
	Graph();
	~Graph();
	int getIndex(const T& v);
	int addVertex(const T& t);
	void addEdge(const T& t1, const T& t2, double border = 0);
	void print();

	void list_n_dfs(int n);
	void border_n_dfs(int n);

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
int Graph<T>::addVertex(const T& t){
	int index = getIndex(t);

	if (index == -1){
		Vertex.push_back(t);
		adj.push_back(std::list<node>());
		index = Vertex.size() -1;
	}

	return index;
}

template <typename T>
void Graph<T>::addEdge(const T& t1, const T& t2, double border) {
	int index1 = addVertex(t1);

	int index2 = addVertex(t2);

	typename std::list<node>::iterator itr;

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
	typename std::list<node>::iterator itr;
	for (int v =0; v < Vertex.size(); v++){
		std::cout<<v<<". "<<"["<<Vertex[v]<<"]";
		for (itr = adj[v].begin(); itr != adj[v].end(); ++itr){
			std::cout<<" -> "<<Vertex[itr->dest]<<": "<<itr->border<<" km";
		}
		std::cout<<std::endl;
	}
}

template <typename T>
void Graph<T>::list_n_dfs(int n){
	bool* visited = new bool[Vertex.size()];
	for (int i=0; i< Vertex.size(); i++){
		visited[i] = false;
	}

	for (int j=0 ; j< Vertex.size(); j++){
		if (!visited[j]){
			list_n_dfs_visit(j, visited, n);
		}
	}


	delete [] visited;
}

template <typename T>
void Graph<T>::list_n_dfs_visit(int u, bool* visited, int n){
	visited[u] = true;

	typename std::list<node>::iterator itr;
	if (adj[u].size() == n){
		std::cout<<u<<". "<<"["<<Vertex[u]<<"]";
		for (itr = adj[u].begin(); itr != adj[u].end(); ++itr){
			std::cout<<" -> "<<Vertex[itr->dest]<<": "<<itr->border<<" km";
		}
		std::cout<<std::endl;
	}

	for (itr = adj[u].begin(); itr != adj[u].end(); ++itr){
		if (!visited[itr->dest]){
			list_n_dfs_visit(itr->dest, visited, n);
		}
	}

}


template <typename T>
void Graph<T>::border_n_dfs(int n){
	bool* visited = new bool[Vertex.size()];
	for (int i=0; i< Vertex.size(); i++){
		visited[i] = false;
	}

	for (int j=0 ; j< Vertex.size(); j++){
		if (!visited[j]){
			border_n_dfs_visit(j, visited, n);
		}
	}


	delete [] visited;
}

template <typename T>
void Graph<T>::border_n_dfs_visit(int u, bool* visited, int n){
	visited[u] = true;

	typename std::list<node>::iterator itr;

	double borders = 0;
	for (itr = adj[u].begin(); itr != adj[u].end(); ++itr){
		borders += itr->border;
	}

	if (borders > n) {
		std::cout<<u<<". "<<"["<<Vertex[u]<<"]";
		for (itr = adj[u].begin(); itr != adj[u].end(); ++itr){
			std::cout<<" -> "<<Vertex[itr->dest]<<": "<<itr->border<<" km";
		}
		std::cout<<std::endl;
	}

	for (itr = adj[u].begin(); itr != adj[u].end(); ++itr){
		if (!visited[itr->dest]){
			border_n_dfs_visit(itr->dest, visited, n);
		}
	}

}


#endif