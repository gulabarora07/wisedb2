#include <bits/stdc++.h>
#include "ModelVM.h"
#include "QueryTimePredictor.h"
using namespace std;


ModelVM::ModelVM(VMType type)
{
	this->type = type;
	queries.clear();
}

void ModelVM::addQuery(ModelQuery mq) 
{
	queries.push_back(mq);
}

void ModelVM::addQueries(std::vector<ModelQuery> toAdd) 
{
	for(int i=0;i<toAdd.size();i++)
		queries.push_back(toAdd[i]);
}

vector<ModelQuery> ModelVM::getQueries() 
{
	return queries;
}

bool ModelVM::popQuery() 
{
	if(queries.size() == 0)
		return false;
	queries.pop_back();
	return true;
}

VMType ModelVM::getType()
{
	return type;
}

int ModelVM::getProvisionTime() 
{
	// TODO: should be loaded from file / more precise based on experiments
	return 20000;
}

int ModelVM::getBootTime() {
	// TODO: should be loaded from file / more precise based on experiments
	return 40000;
}

int ModelVM::getCostForTime(int time) 
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

int ModelVM::getCostForQuery(QueryTimePredictor* qtp, ModelQuery q) {
	int queryTime = qtp->predict(q, this);
	int ioCost = qtp->predictIO(q, this);
	
	ioCost = ceil(((double)ioCost) * 0.000000000005);

	return getCostForTime(queryTime) + ioCost;
}

int ModelVM::getCostForQueries(QueryTimePredictor* qtp) 
{
	int toR = 0;
	for(int i=0;i<queries.size();i++) 
	{
		toR += getCostForQuery(qtp,queries[i]);
	}
	return toR;
}