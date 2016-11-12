#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <cctype>
#include <algorithm>

#include "Graph.h"

using namespace std;

void menu();
string removeStartEndWhiteSpace(const string& s);

template <typename T>
void parseInput(Graph<T>& G);

int main(){

	Graph<string> G;
	parseInput(G);

	int choice;
	int x;
	menu();
	cout<<">";
	cin>>choice;
	

	while (choice != 5){
		
		switch(choice){
			case 1:
			G.print();
			break;

			case 2:
			{
				int id1;
				int id2;

				int input_format;

				string name;

				cout<<"Choose Input format as 0: ID or 1: Name"<<endl;
				cout<<">";
				cin>>input_format;

				if (input_format == 1) {
					cout<<"Enter Name1"<<endl;
					cout<<">";
					cin>>name;

					id1 = G.getIndex(name);

					while (id1 == -1){
						cout<<name<<" not found. Please try again"<<endl;
						cout<<"Enter Name1"<<endl;
						cout<<">";
						cin>>name;
						id1 = G.getIndex(name);
					}

					cout<<"Enter Name2"<<endl;
					cout<<">";
					cin>>name;

					id2 = G.getIndex(name);

					while (id2 == -1){
						cout<<name<<" not found. Please try again"<<endl;
						cout<<"Enter Name2"<<endl;
						cout<<">";
						cin>>name;
						id2 = G.getIndex(name);
					}
				}
				else {
					cout<<"Enter ID1"<<endl;
					cout<<">";
					cin>>id1;

					while (id1 < 0 || id1 >= G.numberVertex()){
						cout<<name<<"ID1 out of range. Please try again"<<endl;
						cout<<"Enter ID1"<<endl;
						cout<<">";
						cin>>id1;
					}

					cout<<"Enter ID2"<<endl;
					cout<<">";
					cin>>id2;

					while (id2 < 0 || id2 >= G.numberVertex()){
						cout<<name<<"ID2 out of range. Please try again"<<endl;
						cout<<"Enter ID2"<<endl;
						cout<<">";
						cin>>id2;
					}
				}			

				G.shortest_path_bfs(id1, id2);
			}

			break;

			case 3:
				cout<<"Enter X"<<endl;
				cout<<">";
				cin>>x;
				G.list_n_dfs(x);
			break;

			case 4:
				cout<<"Enter X"<<endl;
				cout<<">";
				cin>>x;
				G.border_n_dfs(x);
			break;

			default:
			cout<<"Invalid Input choice. Please try again"<<endl;
			break;
		}
		menu();
		cout<<">";
		cin>>choice;
	}


	

	return 0;
}

void menu(){
	cout<<endl;
	cout<<"================ Assignment 5 =================="<<endl;
	cout<<"1. List all countries and bordering countries"<<endl;
	cout<<"2. Find shortest path"<<endl;
	cout<<"3. List all countries with X neighbors"<<endl;
	cout<<"4. Find countries with borders larger than X km"<<endl;
	cout<<"5. Exit"<<endl;
}

string removeStartEndWhiteSpace(const string& s){

	int i,j;
	for (i = 0; i< s.size() && isspace(s[i]); i++) {}
	for (j = s.size() -1; j > i && isspace(s[j]); j--) {}

	return s.substr(i, j-i+1);
}

template <typename T>
void parseInput(Graph<T>& G){
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
			
			if (country_name.size()){

				bool hasANeighbour = false;

				while(getline(input_stream, neighbour_profile, ';')){

					neighbour_profile = removeStartEndWhiteSpace(neighbour_profile);
					
					if (neighbour_profile.size()){
						
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
	input.close();
}