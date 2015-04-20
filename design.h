#ifndef DESIGN_H
#define DESIGN_H
#include <ostream>
#include <vector>
#include <map>
#include <string>
#include "gates.h"
#include "net.h"
#include <algorithm>

using namespace std;

enum {BLACK, GRAY, WHITE};

class Design {
 public:
	Design();
	Design(string n);
	~Design();
	string name() { return desname; }
	void addPI(string n) { pis.push_back(n); } // done
	void addPO(string n) { pos.push_back(n); } // done
	Net *findNet(string net_name); // done
	Gate *findGate(string inst_name); // done
	Net* addFindNet(string n); // done
	Gate* addFindGate(int gtype, string n); // done (but inefficient)
	Gate* addFindGate(int gtype, string n, int d); // done (but inefficient)
	vector<Net *> *getPINets(); // done
	vector<Net *> *getPONets(); // done
	vector<Net *> *getWireNets(); // done
	vector<Net *> *getAllNets(); // done
	vector<Gate *> *getAllGates(); // done
	vector<Net *> *toposort();
	void dump(ostream &os); // done
	bool isPI(Net *n); // done
	bool isPO(Net *n); // done
 private:
	void dfs_visit(Net *n, vector<Net *> *finishedList, map<string, int> &colormap);
	string desname;
	map<string, Net *> designNets;
	map<string, Gate *> designGates;
	vector<string> pis;
	vector<string> pos;

};

#endif
