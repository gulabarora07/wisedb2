/*
	Author		:	Gulab Arora
	Institute	:	IIT Kharagpur
*/
#include <bits/stdc++.h>
#include <unordered_map>
#include <boost/functional/hash_fwd.hpp>
#include <boost/functional/hash.hpp>

#define INF 1e10

/* change code to account for different costs for different machines, change vector<query> to set in vertex */
using namespace std;
typedef double cost_t;

double perVMpenalty;
double startupCost;


/*
	query class
	every query(even same cost) should have unique name
*/

class query{
private:
	friend istream& operator>>(istream &, query &);
	friend ostream& operator<<(ostream &, const query &);
	friend size_t hash_value(const query &);
public:
	string name;
	cost_t cost;
	
	cost_t min_cost(){
		return cost;
	}
	inline bool operator==(const query & other) const{
		return this->name == other.name;
	}
	inline bool operator<(const query & other) const{
		return this->name < other.name;
	}
};

inline istream& operator>>(istream & input, query & q){
	return input>>q.name>>q.cost;
}
inline ostream& operator<<(ostream & output, const query & q){
	return output<<q.name;
}


/*
	class vertex
	//to do
	change vector<query> to set<query>
*/
class vertex{
public:
	vector<query> q;
	int last_machine_no;
	double last_machine_time;
	vertex():last_machine_no(0),last_machine_time(0){}
	vertex(vector<query> & a):q(a),last_machine_no(0),last_machine_time(0){}
	// copy constructor
	vertex(const vertex & other):q(other.q),last_machine_no(other.last_machine_no),last_machine_time(other.last_machine_time){}
	// copy assignment operator
	const vertex & operator=(const vertex & other){
		if(this!=&other){
			this->q = other.q;
			this->last_machine_no = other.last_machine_no;
			this->last_machine_time = other.last_machine_time;
		}
		return *this;
	}
	inline bool same_queries(const vertex & other) const {
		return this->q == other.q;
	}
	// bool comparison = result of comparing 'this' to 'other' on basis of only remaining queries
	inline bool operator==(const vertex & other) const {
		return (this->q == other.q) && (this->last_machine_no == other.last_machine_no);
	}
	inline bool operator!=(const vertex & other) const {
		return !this->operator==(other);
	}
	// required for set
	inline bool operator<(const vertex & other) const {
		return (this->last_machine_no < other.last_machine_no)||(this->q.size() < other.q.size());
	}
private:
	friend void difference(ostream &, const vertex &, const vertex &);
	friend ostream& operator<<(ostream &, const vertex &);
};

ostream& operator<<(ostream & output, const vertex & v){
	output<<"{";
	for(int i = 0; i < v.q.size(); i++){
		output<<v.q[i];
		if(i<(int)v.q.size()-1)
			output<<", ";
	}
	return output<<"}("<<v.last_machine_no<<")";
}

void difference(ostream & output, const vertex & u, const vertex & v){
	output<<u<<"->"<<v<<endl;
	if(u.last_machine_no+1 == v.last_machine_no){
		output<<"Initialize VM"<<endl;
		return;
	}
	set<query> m(v.q.begin(),v.q.end());
	for(int i = 0; i < u.q.size(); i++){
		if(m.find(u.q[i])==m.end()){
			output<<"Assign "<<u.q[i]<<" to "<<u.last_machine_no<<endl;
			return;
		}
	}
	output<<"No difference"<<endl;
}


/*
	functions for computing hash values of query and vertex, do not change it
*/

// only accounts for the name of the query, part of boost, can be called by boost::hash<query>(), required by std::hash<vertex>()
size_t hash_value(const query & x)
{
	boost::hash<string> hasher;
	return hasher(x.name);
}

namespace std {
	// only accounts for the remaining queries, part of std, therefore can be called by std::hash<vertex>()
	template <>
	struct hash<vertex>
	{
		size_t operator()(const vertex & x) const{
			boost::hash<int> hasher;
			size_t seed = hasher(x.last_machine_no);
			boost::hash_range(seed, x.q.begin(), x.q.end());
			return seed;
		}
	};
}
/*

*/


/*
	Graph class
	//to do
	change penalty condition in get_neighbours, add comments
*/
class Graph{
public:
	static cost_t heuristic(vertex & a, vertex & b){
		set<query> m(b.q.begin(),b.q.end());
		cost_t ans = 0;
		for(int i = 0; i < a.q.size(); i++){
			if(m.find(a.q[i])==m.end())
				ans+=a.q[i].min_cost();
		}
		return ans;
	}
	static void get_neighbours(vertex & a, vector<vertex> & neighbors){
		neighbors.clear();
		vertex b;
		if(a.last_machine_time!=0 || a.last_machine_no==0){
			vertex b = a;
			b.last_machine_no++;
			b.last_machine_time = 0;
			neighbors.push_back(b);
		}
		if(a.last_machine_no)
			for(int i = 0; i < a.q.size(); i++){
				if(a.q[i].cost+a.last_machine_time <= perVMpenalty){											/* penalty condition */
					b = a;
					b.q.erase(b.q.begin()+i);
					b.last_machine_time+=a.q[i].cost;
					neighbors.push_back(b);
				}
			}
	}
	static cost_t cost(vertex & a, vertex & b){
		set<query> m(b.q.begin(),b.q.end());
		cost_t ans = 0;
		for(int i = 0; i < a.q.size(); i++){
			if(m.find(a.q[i])==m.end())
				ans+=a.q[i].min_cost();
		}
		if(!ans)
			ans = startupCost+perVMpenalty-a.last_machine_time;
		return ans;
	}
};

// /*
// 	//to do
// 	check it once with harsha, add comments also
// */
// template<typename Graph>
// void a_star_search
// 	(Graph G, vertex start, vertex goal,
// 	function<typename Graph::cost_t(const vertex & a, const vertex & b)> heuristic,
// 	unordered_map<vertex, vertex, boost::hash<vertex> >& came_from,
// 	unordered_map<vertex, typename Graph::cost_t, boost::hash<vertex> >& cost_so_far)
// {
// 	typedef typename Graph::vertex vertex;
// 	typedef typename Graph::cost_t cost_t;

// 	unordered_map<vertex, cost_t, boost::hash<vertex> >& priority;
// 	set<pair<cost_t,vertex> > frontier;
// 	vector<vertex> neighbors;

// 	frontier.put(start, cost_t(0));
// 	came_from[start] = start;
// 	cost_so_far[start] = cost_t(0);
	
// 	while (!frontier.empty()) {
// 		vertex current = frontier.begin()->second;
// 		frontier.erase(frontier.begin());
// 		if (current == goal) {
// 			break;
// 		}
// 		G.get_neighbors(current, neighbors);
// 		for (vertex next : neighbors) {
// 			cost_t new_cost = cost_so_far[current] + Graph::cost(current, next);
// 			if(cost_so_far.find(next) == cost_so_far.end()){
// 				cost_so_far[next] = INF;
// 				priority[next] = INF;
// 			}
// 			if (new_cost < cost_so_far[next]) {
// 				cost_so_far[next] = new_cost;
// 				auto & next_priority = priority.find(next);
// 				frontier.erase(mp(next_priority->second,next));
// 				next_priority = new_cost + heuristic(next, goal);
// 				frontier.insert(mp(next_priority->second,next));
// 				came_from[next] = current;
// 			}
// 		}
// 	}
// }


/*
	dijkstra set implementation
*/
void dijkstra(vertex & start, vertex & goal, bool print_on,
	unordered_map<vertex, vertex> & came_from,
	unordered_map<vertex, cost_t> & cost_so_far)
{
	set<pair<cost_t,vertex> > frontier;
	vector<vertex> neighbours;

	frontier.insert(make_pair(cost_t(0), start));
	came_from[start] = start;
	cost_so_far[start] = cost_t(0);
	if(print_on) cout<<"Start is "<<start<<" and Goal is "<<goal<<endl;

	while (!frontier.empty()) {
		vertex current = frontier.begin()->second;
		frontier.erase(frontier.begin());

		if(print_on) cout<<current<<": \t";
		
		if (current.same_queries(goal)){
			goal = current;
			if(print_on) cout<<"reached goal with "<<current<<endl;
			break;
		}
		
		Graph::get_neighbours(current, neighbours);
		for (vertex next : neighbours) {
			
			if(print_on) cout<<next<<"\t";

			cost_t new_cost = cost_so_far[current] + Graph::cost(current, next);
			if(cost_so_far.find(next) == cost_so_far.end())
				cost_so_far[next] = INF;
			
			if (new_cost < cost_so_far[next]) {
				frontier.erase(make_pair(cost_so_far[next],next));
				cost_so_far[next] = new_cost;
				came_from[next] = current;
				frontier.insert(make_pair(cost_so_far[next],next));
			}
		}
		if(print_on) cout<<endl;
	}
}

/*
	read penalty parameters also, name of every query should be different
*/

int main(){
	int n;
	cin>>n;
	cin>>perVMpenalty;
	cin>>startupCost;
	vector<query> q(n);
	for(int i = 0; i < n; i++)
		cin>>q[i];
	vertex st(q), goal;
	unordered_map<vertex, vertex, std::hash<vertex> > came_from;
	unordered_map<vertex, cost_t> cost_so_far;
	dijkstra(st,goal,false,came_from,cost_so_far);
	vertex u = goal;
	stringstream ss;
	stack<string> s;
	while(u!=st){
		vertex v = came_from[u];
		difference(ss,v,u);
		s.push(ss.str());
		ss.str("");
		u = v;
	}
	while(!s.empty()){
		cout<<s.top()<<endl;
		s.pop();
	}
}

/*
some testing inputs:
5 5 1 
a 2 b 3 c 4 d 2.5 e 4

3 3 5
a 2 b 2 c 1
*/