// net.cpp
#include <algorithm>
#include "net.h"
#include "gates.h"

using namespace std;

Net::Net()
{
	netname = "";
	val = 'X';
	delay = 0;
	drivers = new vector<Gate *>;
	loads = new vector<Gate *>;
}

Net::Net(string n)
{
	netname = n;
	val = 'X';
	delay = 0;
	drivers = new vector<Gate *>;
	loads = new vector<Gate *>;
}

Net::~Net()
{
/*
	vector<Gate *>::iterator it;
	for (it = drivers->begin(); it != drivers->end(); it++)
	{
		delete *it;
	}
	for (it = loads->begin(); it != loads->end(); it++)
	{
		delete *it;
	}
*/
	delete drivers;
	delete loads;
}

void Net::printDriversLoads()
{
    vector<Gate *>::iterator it;
	cout << "Drivers: ";
    for(it=drivers->begin();it!=drivers->end();it++){
        cout<<(*it)->name()<<"  ";
    }
    cout<<endl;
	cout << "Loads: ";
    for(it=loads->begin();it!=loads->end();it++){
        cout<<(*it)->name()<<"  ";
    }
    cout<<endl;
}

char Net::computeVal()
{
//cout << endl << "current net: " << this->name() << endl << endl;
	int numDrivers = drivers->size();
/*
cout << "numDrivers = " << numDrivers << endl;
cout << "current val is = " << this->getVal() << endl;
this->printDriversLoads();
*/


	// if no drivers (principal input)
	// simply return the current value
	if ( numDrivers == 0 )
		return getVal();

	// if only one driver
	// normal operation: just evaluate the gate and return that value
	if ( numDrivers == 1 )
	{
		val = drivers->at(0)->eval();
//cout << "val = " << val << endl;
		return val;
	}

	// if multiple drivers...
	// calculate all results
	// compare them
	// if they are not all the same
	// return 'X'
	char * allVals = new char[numDrivers];

	for (int i=0; i < numDrivers; i++)
	{
		allVals[i] = drivers->at(i)->eval();
	}

	// checking for uniformity
	char previous = allVals[0];
	char next;
	for (int i=1; i < numDrivers; i++)
	{
		next = allVals[i];
		if ( next != previous )
			return 'X';
	}

	delete [] allVals;

	return val;
}

//not sure how to call functions in gate class
int Net::computeDelay()
{
/*    delay=0;
    vector<Gate *>::iterator it;
    for(it=drivers->begin();it!=drivers->end();it++)
    {
        if((*it)->getDelay()>delay) delay=(*it)->getDelay();
    }
    return delay;*/
	
	// 
	int maxNetDelay = 0, maxDelay = 0;
	int tempNetDelay, tempGateDelay, tempDelay;

	vector<Gate *>::iterator gt;
	vector<Net *>::iterator nt;

	for (gt = drivers->begin(); gt != drivers->end(); gt++)
	{
		// reset net delay
		maxNetDelay = 0;
		for (nt = (*gt)->getInputs()->begin(); nt != (*gt)->getInputs()->end(); nt++)
		{
			tempNetDelay = (*nt)->getDelay();
			if ( tempNetDelay > maxNetDelay )
				maxNetDelay = tempNetDelay;
		}
		tempGateDelay = (*gt)->getDelay();
		tempDelay = maxNetDelay + tempGateDelay;
		if ( tempDelay > maxDelay )
			maxDelay = tempDelay;
	}
	return maxDelay;
}
