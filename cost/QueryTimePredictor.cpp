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


QueryTimePredictor::QueryTimePredictor(vector<VMType> type,int numQ) {
	(this->types).clear();
	for(int i=0;i<type.size();i++)
	{
		// cout<<type[i].getId()<<" kdn"<<endl;
		(this->types).push_back(type[i]);
	}
	loadValuesFromJSON(numQ);
}

QueryTimePredictor::QueryTimePredictor() {
	(this->types).clear();
	for(int i=0;i<7;i++)
	{
		VMType temp1(i);
		// cout<<type[i].getId()<<" kdn"<<endl;
		(this->types).push_back(temp1);
	}
	loadValuesFromJSON(16);
}

void QueryTimePredictor::loadValuesFromJSON(int numQ) {
	latencyData.clear();
	ioData.clear();
	QUERY_TYPES.clear();

	for(int i=0;i<numQ;i++)
	{
		QUERY_TYPES.push_back(i);
		map<VMType, int> latency;
		map<VMType, int> io;

		latency.clear();
		io.clear();

		for(int j=0;j<types.size();j++)
		{
			latency[types[j]] = rand()%50000;//random value;
			io[types[j]] = rand()%50000;//random value;
		}

		latencyData[i] = latency;
		ioData[i] = io;

		// cout<<"io,lat "<<io.size()<<" "<<latency.size()<<endl;
	}
	// cout<<"size of latency "<<latencyData.size()<<endl;
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

	cout<<"QueryType VMType Cost\n";
	VMType t1(0);
	VMType t2(1);
	ModelVM *small= new ModelVM(t1);
	ModelVM *medium = new ModelVM(t2);
	for (int i=0;i<QUERY_TYPES.size();i++) {
		ModelQuery q(i);
		// cout<<i<<"\t"<<medium->getCostForQuery(this, q)<<"\t"<<small->getCostForQuery(this, q)<<endl;
		for(int j=0;j<types.size();j++)
		{
			ModelVM *temp = new ModelVM(types[j]);
			cout<<i<<"\t"<<j<<"\t"<<temp->getCostForQuery(this,q)<<endl;
		}
	}
}
