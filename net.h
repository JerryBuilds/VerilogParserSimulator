#ifndef NET_H
#define NET_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Gate; // forward declaration

class Net {
 public:
	Net();
	Net(string n);
	~Net();
	void printDriversLoads();
	char computeVal();
	int computeDelay();
	// mutators
	void addDriver(Gate *g) { drivers->push_back(g); }
	void addLoad(Gate *g) { loads->push_back(g); }
	void setVal(char v) { val = v; }
	void setDelay(int d) { delay = d; }
	// accessors
	string name() { return netname; }
	vector<Gate *> *getLoads() { return loads; }
	vector<Gate *> *getDrivers() { return drivers; }
	char getVal() { return val; }
	int getDelay() { return delay; }

 private:
	vector<Gate *> *drivers;
	vector<Gate *> *loads;
	char val;
	string netname;
	int delay;
};
#endif
