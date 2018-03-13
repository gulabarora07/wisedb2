#include <bits/stdc++.h>
using namespace std;
#include "Cost.h"

void Cost::setQueriesCost(int cost)
{
	queriesCost = cost;
}

void Cost::setVMBootCost(int cost)
{
	VMBootCost = cost;
}

void Cost::setPenaltyCost(int cost)
{
	penaltyCost = cost;
}

int Cost::getQueriesCost()
{
	return queriesCost;
}
int Cost::getVMBootCost()
{
	return VMBootCost;
}
int Cost::getPenaltyCost()
{
	return penaltyCost;
}

int Cost::getTotalCost()
{
	return (queriesCost + VMBootCost + penaltyCost);
}

string Cost::toString(){
	return "total Cost: "+std::to_string(getTotalCost())+", queries cost: "+std::to_string(queriesCost)+
			", VM boot cost: "+std::to_string(VMBootCost)+", penalty cost: "+std::to_string(penaltyCost);
}

string Cost::toCSV() {
// return CSV boot,queries,penalty
	return std::to_string(getVMBootCost()) + ", " + std::to_string(getQueriesCost()) + ", " + std::to_string(getPenaltyCost());
}
