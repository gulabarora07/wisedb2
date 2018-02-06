/*
	Author		:	Gulab Arora
	Institute	:	IIT Kharagpur
*/
#include <bits/stdc++.h>
#include <unordered_map>
#include <boost/functional/hash_fwd.hpp>
#include <boost/functional/hash.hpp>

#define INF 1e10

using namespace std;

/* change code to account for different costs for different machines */

/*
	query class
	every query(even same cost) should have unique name
*/

class query{
	typedef double cost_t;
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

istream& operator>>(istream & input, query & q){
	return input>>q.name>>q.cost;
}
ostream& operator<<(ostream & output, const query & q){
	return output<<q.name;
}


/*
	struct vertex
*/
typedef struct vertex{
	vector<query> q;
	int last_machine_no;
	double last_machine_time;
	vertex():last_machine_no(0),last_machine_time(0){}

	// bool comparison = result of comparing 'this' to 'other' on basis of only remaining queries
	inline bool operator==(const vertex & other) const {
		return this->q == other.q;
	}
private:
	friend size_t hash_value(const vertex &);
}vertex;


/*
	functions for computing hash values of query and vertex, do not change it
*/
namespace std {
	inline size_t hash_value(const query & x){
		boost::hash<string> hasher;
		return hasher(x.name);
	}
	// only accounts for the remaining queries
	inline size_t hash_value(const vertex & x){
		return boost::hash_range(x.q.begin(), x.q.end());
	}
}


/*
	Graph class
	//to do
	change penalty condition in get_neighbours, add comments
*/
template<typename query>
class Graph{
public:
	typedef typename query::cost_t cost_t;
	cost_t heuristic(vertex & a, vertex & b){
		set<query> m(b.q.begin(),b.q.end());
		cost_t ans = 0;
		for(int i = 0; i < a.q.size(); i++){
			if(m.find(a.q[i])==m.end())
				ans+=a.q[i].min_cost();
		}
		return ans;
	}
	void get_neighbours(vertex & a, vector<vertex> & neighbors){
		neighbors.clear();
		vertex b = a;
		b.last_machine_time++;
		b.last_machine_time = 0;
		neighbors.push_back(b);
		for(int i = 0; i < (int)a.q.size()-1; i++){
			if(true){											/* penalty condition */
				b = a;
				b.q.erase(b.q.begin()+i);
				b.last_machine_time+=a.q[i].cost();
				neighbors.push_back(b);
			}
		}
	}
};

/*
	//to do
	check it once with harsha, add comments also
*/
template<typename Graph>
void a_star_search
	(Graph G, vertex start, vertex goal,
	function<typename Graph::cost_t(const vertex & a, const vertex & b)> heuristic,
	unordered_map<vertex, vertex, boost::hash<vertex> >& came_from,
	unordered_map<vertex, typename Graph::cost_t, boost::hash<vertex> >& cost_so_far)
{
	typedef typename Graph::vertex vertex;
	typedef typename Graph::cost_t cost_t;

	unordered_map<vertex, cost_t, boost::hash<vertex> >& priority;
	set<pair<cost_t,vertex> > frontier;
	vector<vertex> neighbors;

	frontier.put(start, cost_t(0));
	came_from[start] = start;
	cost_so_far[start] = cost_t(0);
	
	while (!frontier.empty()) {
		vertex current = frontier.begin()->second;
		frontier.erase(frontier.begin());
		if (current == goal) {
			break;
		}
		G.get_neighbors(current, neighbors);
		for (vertex next : neighbors) {
			cost_t new_cost = cost_so_far[current] + G.cost(current, next);
			if(cost_so_far.find(next) == cost_so_far.end()){
				cost_so_far[next] = INF;
				priority[next] = INF;
			}
			if (new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				auto & next_priority = priority.find(next);
				frontier.erase(mp(next_priority->second,next));
				next_priority = new_cost + heuristic(next, goal);
				frontier.insert(mp(next_priority->second,next));
				came_from[next] = current;
			}
		}
	}
}

/*
	read penalty parameters also, name of every query should be different
*/

int main(){
	int n;
	cin>>n;
	vector<query> q(n);
	for(int i = 0; i < n; i++){
		cin>>q[i];
		cout<<q[i]<<endl;
	}
}
