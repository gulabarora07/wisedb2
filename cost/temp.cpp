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
