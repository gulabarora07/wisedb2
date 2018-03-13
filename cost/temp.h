#include <bits/stdc++.h>
using namespace std;

#ifndef VMType_H
#define VMType_H

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
		VMType(int id = 0);
		int getCost();
		string toString();
		int getId();
		bool operator< (const VMType& c) const;
};

#endif

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

#ifndef ModelQuery_H
#define ModelQuery_H

class ModelQuery
{
	int type;
	// Should we make it atomic? Not necessary i think
	static int count;
	public:
		ModelQuery(int type);
		int getType();
};

#endif