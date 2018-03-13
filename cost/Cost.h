#include <bits/stdc++.h>
using namespace std;

#ifndef Cost_H
#define Cost_H

class Cost
{
	private:
		int queriesCost;
		int VMBootCost;
		int penaltyCost;
	public:
		void setQueriesCost(int cost);
		void setVMBootCost(int cost);
		void setPenaltyCost(int cost);
		int getQueriesCost();
		int getVMBootCost();
		int getPenaltyCost();
		int getTotalCost();

		string toString();
	
		string toCSV();
};

#endif
