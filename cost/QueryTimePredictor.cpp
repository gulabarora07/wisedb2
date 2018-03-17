#include <bits/stdc++.h>
#include "QueryTimePredictor.h"
#include "ModelVM.h"
using namespace std;



QueryTimePredictor::QueryTimePredictor(map<int, map<VMType, int> > latency, map<int, map<VMType, int> > ioData, vector<VMType> types) {
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

QueryTimePredictor::QueryTimePredictor(vector<VMType> types) {
	this->types = types;
	loadValuesFromJSON();
}

QueryTimePredictor::QueryTimePredictor() {
	loadValuesFromJSON();
}

void QueryTimePredictor::loadValuesFromJSON() {
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

int QueryTimePredictor::predict(ModelQuery q, ModelVM* vm) {
	return predict(q, vm->getType());
}

int QueryTimePredictor::predictIO(ModelQuery q, ModelVM* vm) {
	if (ioData.find(q.getType()) == ioData.end())
		return INT_MAX;
	return ioData[q.getType()][vm->getType()];
}

/**
 * Predicts the cost of a query ran on a certain type of VM
 * 
 * @param q the query to cost
 * @param vm the VM to calculate the query cost for
 * @return the cost of the query
 */
int QueryTimePredictor::predict(ModelQuery q, VMType vm) {

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

VMType QueryTimePredictor::getOneVM() {
	return types[0];
}

void QueryTimePredictor::check()
{
	for(int i=0;i<QUERY_TYPES.size();i++)
	{
		ModelVM* vm = new ModelVM(3);
		ModelQuery q(i);
		int tym = predict(q,vm);
		int ios = predictIO(q,vm);
		cout<<i<<", "<<tym<<" ("<<ios<<" IOs)"<<endl;
	}

	cout<<"Type\tt2.med\tt2.small\n";
	VMType t1(0);
	VMType t2(1);
	ModelVM *small= new ModelVM(t1);
	ModelVM *medium = new ModelVM(t2);
	for (int i=0;i<QUERY_TYPES.size();i++) {
		ModelQuery q(i);
		cout<<i<<"\t"<<medium->getCostForQuery(this, q)<<"\t"<<small->getCostForQuery(this, q)<<endl;

	}
}
