#include <bits/stdc++.h>
using namespace std;

#include "VMType.h"

VMType::VMType(int i)
{
	this->id = i;
}
int VMType::getCost() 
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

string VMType::toString() {
	switch (this->id) {
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
			return "unit";
		default:
			return "not valid VMType";
	}
}
int VMType::getId() const
{
	return id;
}

bool VMType::operator< (const VMType& c) const
{
	return (this->id < c.id);
}

void VMType::operator= (const VMType &c)
{
	this->id = c.getId();
}