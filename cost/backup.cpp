#include <bits/stdc++.h>
using namespace std;



class VMType 
{
	int id;
	// T2_SMALL 0, T2_MEDIUM 1, M3_MEDIUM 2, M3_LARGE 3, C4_LARGE 4, C4_XLARGE 5, UNIT 6;

	/**
	 * Gets the cost per hour in 1/10 of a cent
	 * 2.6 cents per hour will be returned as 26 
	 * 
	 * @return the cost per hour in 1/10 of a cent
	 */
	public:
		VMType(int id = 0)
		{
			this->id = id;
		}
		int getCost() 
		{
			switch(id) 
			{
				case 4:   // C4_LARGE
					return 1160;
				case 5:
					return 2320;
				case 3:
					return 1400;
				case 2:
					return 700;
				case 1:
					return 520;
				case 0:
					return 260;
				case 6:
					return 1000*60*60; // costs 1 per milisecond
				default:
					return INT_MAX;
			}
		}

		string toString() {
			switch(id) 
			{
				case 4:
					return "c4.large";
				case 5:
					return "c4.xlarge";
				case 3:
					return "m3.large";
				case 2:
					return "m3.medium";
				case 1:
					return "t2.medium";
				case 0:
					return "t2.small";
				case 6:
					return "unit VM";
				default:
					return "unknown";
			}
		}

		// int fromString(string s) {
		// 	switch (s) {
		// 		case "c4.large":
		// 			return 4;
		// 		case "c4.xlarge":
		// 			return 5;
		// 		case "m3.large":
		// 			return 3;
		// 		case "m3.medium":
		// 			return 2;
		// 		case "t2.medium":
		// 			return 1;
		// 		case "t2.small":
		// 			return 0;
		// 		case "unit":
		// 			return 6;
		// 		default:
		// 			return null;
		// 	}
		// }

		int getId()
		{
			return id;
		}

		bool operator< (const VMType& c) const
		{
			return (this->id < c.id);
		}
};

class Cost
{
	private:
		int queriesCost;
		int VMBootCost;
		int penaltyCost;
	public:
		void setQueriesCost(int cost)
		{
			queriesCost = cost;
		}
		
		void setVMBootCost(int cost)
		{
			VMBootCost = cost;
		}
		
		void setPenaltyCost(int cost)
		{
			penaltyCost = cost;
		}
		
		int getQueriesCost()
		{
			return queriesCost;
		}
		int getVMBootCost()
		{
			return VMBootCost;
		}
		int getPenaltyCost()
		{
			return penaltyCost;
		}
	
		int getTotalCost()
		{
			return (queriesCost + VMBootCost + penaltyCost);
		}

		string toString(){
			return "total Cost: "+std::to_string(getTotalCost())+", queries cost: "+std::to_string(queriesCost)+
					", VM boot cost: "+std::to_string(VMBootCost)+", penalty cost: "+std::to_string(penaltyCost);
		}
	
		string toCSV() {
		// return CSV boot,queries,penalty
			return std::to_string(getVMBootCost()) + ", " + std::to_string(getQueriesCost()) + ", " + std::to_string(getPenaltyCost());
		}
};


class ModelQuery
{
	int type;
	// Should we make it atomic? Not necessary i think
	static int count;

	public:
		ModelQuery(int type) {
			this->type = type;
			count++;
		}
	
		int getType() {
			return type;
		}
};


class ModelVM
{
	vector<ModelQuery> queries;
	VMType type;       // default set to 0
	public:
		ModelVM(VMType type)
		{
			this->type = type;
			queries.clear();
		}
		void addQuery(ModelQuery mq) 
		{
			queries.push_back(mq);
		}
		
		void addQueries(std::vector<ModelQuery> toAdd) 
		{
			for(int i=0;i<toAdd.size();i++)
				queries.push_back(toAdd[i]);
		}

		vector<ModelQuery> getQueries() 
		{
			return queries;
		}

		bool popQuery() 
		{
			if(queries.size() == 0)
				return false;
			queries.pop_back();
			return true;
		}

		VMType getType()
		{
			return type;
		}

		int getProvisionTime() 
		{
			// TODO: should be loaded from file / more precise based on experiments
			return 20000;
		}

		int getBootTime() {
			// TODO: should be loaded from file / more precise based on experiments
			return 40000;
		}

		int getCostForTime(int time) 
		{
			// convert miliseconds to hours
			double hours = (double)time / 1000.0;
			hours /= 60;
			hours /= 60;

			// we need to add in the EBS cost
			// which is 0.05 cents / GB month
			// $0.000007 per hour
			double IOcost = 0.000007;

			// return the cost
			double cost = ((type.getCost() * hours) + (IOcost * hours));
			return (int) ceil(cost);
			
			//TODO : reset
			//return time;
		}

		int getCostForQuery(QueryTimePredictor* qtp, ModelQuery q) {
			int queryTime = qtp->predict(q, *this);
			int ioCost = qtp->predictIO(q, *this);
			
			ioCost = ceil(((double)ioCost) * 0.000000000005);

			return getCostForTime(queryTime) + ioCost;
		}

		int getCostForQueries(QueryTimePredictor* qtp) 
		{
			int toR = 0;
			for(int i=0;i<queries.size();i++) 
			{
				toR += getCostForQuery(qtp,queries[i]);
			}
			return toR;
		}
};

class QueryTimePredictor {

	map<int, map<VMType, int> > latencyData;
	map<int, map<VMType, int> > ioData;

	vector<int> QUERY_TYPES;
	
	vector<VMType> types;
	
	public:
		QueryTimePredictor(map<int, map<VMType, int> > latency, map<int, map<VMType, int> > ioData, vector<VMType> types) {
			latencyData = latency;
			this->ioData = ioData;
			map<int, map<VMType, int> >::iterator it;

			(this->QUERY_TYPES).clear();
			(this->types).clear();

			for(it=latency.begin();it!=latency.end();it++)
				(this->QUERY_TYPES).push_back(it->first);

			this->types = types;
		}
		
		// public QueryTimePredictor(map<int, map<VMType, int> > latency, map<int, map<VMType, int> > ioData) {
		// 	latencyData = latency;
		// 	this->ioData = ioData;
		// 	map<int, map<VMType, int> >::iterator it;

		// 	(this->QUERY_TYPES).clear();
		// 	(this->types).clear();

		// 	for(it=latency.begin();it!=latency.end();it++)
		// 		(this->QUERY_TYPES).push_back(it->first);
		// }
		
		QueryTimePredictor(vector<VMType> types) {
			this->types = types;
			loadValuesFromJSON();
		}
		
		QueryTimePredictor() {
			loadValuesFromJSON();
		}
		
		void loadValuesFromJSON() {
			latencyData.clear();
			ioData.clear();
			QUERY_TYPES.clear();

			for(int i=0;i<16;i++)
			{
				QUERY_TYPES.push_back(i);
				map<VMType, int> latency;
				map<VMType, int> io;

				for(int j=0;j<types.size();j++)
				{
					latency[types[j]] = rand()%50;//random value;
					io[types[j]] = rand()%50;//random value;
				}

				latencyData[i] = latency;
				ioData[i] = io;
			}
			// Yet to be implemented

		}

		int predict(ModelQuery q, ModelVM vm) {
			return predict(q, vm.getType());
		}

		int predictIO(ModelQuery q, ModelVM vm) {
			if (ioData.find(q.getType()) == ioData.end())
				return INT_MAX;
			return ioData[q.getType()][vm.getType()];
		}

		/**
		 * Predicts the cost of a query ran on a certain type of VM
		 * 
		 * @param q the query to cost
		 * @param vm the VM to calculate the query cost for
		 * @return the cost of the query
		 */
		int predict(ModelQuery q, VMType vm) {

			if ((latencyData.find(q.getType()) == latencyData.end())
					|| (latencyData[q.getType()].find(vm) == latencyData[q.getType()].end()))
				throw ("Could not find latency data for query " + to_string(q.getType()) + " on " + vm.toString());
			
			return latencyData[q.getType()][vm];
		}

		// Set<ModelVM> getNewVMs() {
		// 	Set<ModelVM> toR = new HashSet<ModelVM>();

		// 	for (VMType t : types) {
		// 		toR.add(new ModelVM(t));

		// 	}

		// 	return toR;
		// }
		
		VMType getOneVM() {
			return types[0];
		}

		void check()
		{
			for(int i=0;i<QUERY_TYPES.size();i++)
			{
				ModelVM vm(3);
				ModelQuery q(i);
				int tym = predict(q,vm);
				int ios = predictIO(q,vm);
				cout<<i<<", "<<tym<<" ("<<ios<<" IOs)"<<endl;
			}

			cout<<"Type\tt2.med\tt2.small\n";
			VMType t1(0);
			VMType t2(1);
			ModelVM small(t1);
			ModelVM medium(t2);
			for (int i=0;i<QUERY_TYPES.size();i++) {
				ModelQuery q(i);
				cout<<i<<"\t"<<medium.getCostForQuery(*this, q)<<"\t"<<small.getCostForQuery(*this, q)<<endl;

			}
		}

};

int main()
{
	vector<VMType> v;

	// Decide which types of v you want
	VMType temp1(0);
	v.push_back(temp1);
	VMType temp2(1);
	v.push_back(temp2);
	
	QueryTimePredictor qtp(v);
	qtp.check();	
}