#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <cctype>
#include <algorithm>

using namespace std;

string removeStartEndWhiteSpace(const string& s);

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
	vector<T> Vertex;
	vector< list<node> > adj;


public:
	Graph();
	~Graph();
	int getIndex(const T& v);
	int addVertex(const T& t);
	void addEdge(const T& t1, const T& t2, double border = 0);
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
int Graph<T>::addVertex(const T& t){
	int index = getIndex(t);

	if (index == -1){
		Vertex.push_back(t);
		adj.push_back(list<node>());
		index = Vertex.size() -1;
	}

	return index;
}

template <typename T>
void Graph<T>::addEdge(const T& t1, const T& t2, double border) {
	int index1 = addVertex(t1);

	int index2 = addVertex(t2);

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
			cout<<" -> "<<Vertex[itr->dest]<<": "<<itr->border<<" km";
		}
		cout<<endl;
	}
}

int main(){
	Graph<string> G;

	ifstream input;
	input.open("countries.dat");

	string line;
	string country_name;
	string neighbour_profile;
	string neighbour_name;
	double border;

	while(getline(input,line)){		
		stringstream input_stream(line);

		bool isRead = (getline(input_stream, country_name, '>'));
		if (isRead){

			input_stream.get();
			country_name = removeStartEndWhiteSpace(country_name);
			bool countryExist = (country_name.size() > 0) ? true : false;

			if (countryExist){

				bool hasANeighbour = false;

				while(getline(input_stream, neighbour_profile, ';')){

					neighbour_profile = removeStartEndWhiteSpace(neighbour_profile);
					bool neighbourExist = (neighbour_profile.size() > 0) ? true : false;

					if (neighbourExist){
						
						hasANeighbour = true;

						int indexDist;
						for (indexDist=0; indexDist< neighbour_profile.size() && neighbour_profile[indexDist] != ':'; indexDist++){}

						neighbour_name = neighbour_profile.substr(0,indexDist);
						neighbour_name = removeStartEndWhiteSpace(neighbour_name);

						bool hasBorder = false;
						border = 0;

						if (neighbour_name.size() < neighbour_profile.size()){
							string Distance = neighbour_profile.substr(indexDist+1, string::npos);
							Distance = removeStartEndWhiteSpace(Distance);

							if (Distance.size() > 2){
								Distance = Distance.substr(0,Distance.size()-2);
								Distance = removeStartEndWhiteSpace(Distance);
								Distance.erase(remove(Distance.begin(), Distance.end(), ','), Distance.end());

								if (Distance.size()){
									hasBorder = true;
									border = atof(Distance.c_str());								
								}
							}
						}

						G.addEdge(country_name, neighbour_name, border);
						
					}
				}

				if (!hasANeighbour){
					G.addVertex(country_name);
				}

			}

		}

	}

	G.print();

	return 0;
}

string removeStartEndWhiteSpace(const string& s){

	int i,j;
	for (i = 0; i< s.size() && isspace(s[i]); i++) {}
	for (j = s.size() -1; j > i && isspace(s[j]); j--) {}

	return s.substr(i, j-i+1);
}