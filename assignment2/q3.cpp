#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

template <typename elem>
class dlist;

template <typename elem>
class deck;

template <typename elem>
class dlist {
private:	
	class node {
	public:
		elem val;
		node* next;
		node* prev;
	};
private:
	node* header;
	node* trailer;
public:
	dlist();
	~dlist();
	bool empty() const;
	const elem& front() const;
	const elem& back() const;
	void addfront(const elem& e);
	void addback(const elem& e);
	void removeback();
	void removefront();

protected:
	void add(node* v, const elem& e);
	void remove(node* v);
};

template <typename elem>
dlist<elem>::dlist() {
	header  = new node();
	trailer = new node();
	header->next = trailer;
	trailer->prev = header;
}

template <typename elem>
dlist<elem>::~dlist() {
	while(!empty()){
		removefront();
	}
	delete header;
	delete trailer;
}

template <typename elem>
bool dlist<elem>::empty() const{
	return (header->next == trailer);
}

template <typename elem>
const elem& dlist<elem>::front() const {
	return (header->next->val);
}

template <typename elem>
const elem& dlist<elem>::back() const{
	return (trailer->prev->val);
}

template <typename elem>
void dlist<elem>::addfront(const elem& e){
	add(header->next,e);
}

template <typename elem>
void dlist<elem>::addback(const elem& e){
	add(trailer,e);
}

template <typename elem>
void dlist<elem>::removeback(){
	remove(trailer->prev);
}

template <typename elem>
void dlist<elem>::removefront(){
	remove(header->next);
}


template <typename elem>
void dlist<elem>::add(node* v, const elem& e){
	node* toad = new node();
	toad->val = e;
	toad->prev = v->prev;
	toad->next = v;
	(v->prev)->next = v->prev = toad;
}

template <typename elem>
void dlist<elem>::remove(node* v){
	node* u = v->prev;
	node* w = v->next;
	u->next = w;
	w->prev = u;
	delete v;
}

template <typename elem>
class deck{
private:
	dlist<elem> d;
	int n;
public:
	deck();
	~deck();
	int size() const;
	bool empty() const;
	void push_front(const elem& e);
	void pop_front();
	void push_back(const elem& e);
	void pop_back();
	const elem& front() const;
	const elem& back() const;
};

template <typename elem>
deck<elem>::deck(): d(), n(0) {}

template <typename elem>
deck<elem>::~deck() {}

template <typename elem>
int deck<elem>::size() const{
	return n;
}

template <typename elem>
bool deck<elem>::empty() const{
	return (n==0);
}

template <typename elem>
void deck<elem>::push_front(const elem& e){
	d.addfront(e);
	n++;
}

template <typename elem>
void deck<elem>::pop_front(){
	d.removefront();
	n--;
}

template <typename elem>
void deck<elem>::push_back(const elem& e){
	d.addback(e);
	n++;
}

template <typename elem>
void deck<elem>::pop_back(){
	d.removeback();
	n--;
}

template <typename elem>
const elem& deck<elem>::front() const{
	return d.front();
}

template <typename elem>
const elem& deck<elem>::back() const{
	return d.back();
}


int main() {
	
	ifstream input;
	input.open("input3.txt");

	string line;

	ofstream output;
	output.open("2015csb1021-output3.txt", ios::out | ios::trunc);

	while(getline(input,line)){
		stringstream input_stream(line);

		vector<int> inArray;
		int k = 0;
		int n = 0;
		input_stream>>k;
		
		int temp;
		while(input_stream>>temp){
			inArray.push_back(temp);
			n++;
		}

		if(n==0){
			output<<"Invalid input: Input sequence is of size zero"<<endl;
		}
		else if (k == 0) {
			output<<"Invalid input: Subarray size is zero"<<endl;
		}
		else if (k>n) {
			output<<"Invalid input: Subarray size is more than array size"<<endl;
		}
		else {
			
			vector<int> ansMax;
			vector<int> ansMin;


			deck<int> max;

			for(int i=0;i<k;i++){
				while(!max.empty() && inArray[max.back()] < inArray[i]){
					max.pop_back();
				}

				max.push_back(i);
			}

			for(int i=k;i<n;i++){
				ansMax.push_back(inArray[max.front()]);

				while(!max.empty() && max.front() <= i-k){
					max.pop_front();
				}
				while(!max.empty() && inArray[max.back()] < inArray[i]){
					max.pop_back();
				}
				max.push_back(i);

			}

			ansMax.push_back(inArray[max.front()]);


			deck<int> min;

			for(int i=0;i<k;i++){
				while(!min.empty() && inArray[min.back()] > inArray[i]){
					min.pop_back();
				}

				min.push_back(i);
			}

			for(int i=k;i<n;i++){
				ansMin.push_back(inArray[min.front()]);

				while(!min.empty() && min.front() <= i-k){
					min.pop_front();
				}
				while(!min.empty() && inArray[min.back()] > inArray[i]){
					min.pop_back();
				}
				min.push_back(i);

			}
			
			ansMin.push_back(inArray[min.front()]);

			for (int j=0; j< (n-k+1);j++){
				output<<"("<<ansMin[j]<<","<<ansMax[j]<<")";
				if (j< n-k) {
					output<<" ";
				}
				else if (j == n-k) {
					output<<endl;
				}
			}
		}

	}
	input.close();
	output.close();
	return 0;
}