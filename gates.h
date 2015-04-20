#ifndef GATE_H
#define GATE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "net.h"

using namespace std;

// forward declaration
class Net;

enum {AND, OR, NAND, NOR, XOR, NOT};

class Gate {
 public:
	Gate();
	Gate(string n); // no delay provided
	Gate(string n, int d);  // with delay provided
	virtual ~Gate();
	virtual char eval() = 0;
	virtual void dump(ostream &os) = 0;
	// mutators
	void addInput(Net *n) { inputs->push_back(n); }
	void addOutput(Net *n) { output = n; }
	// accessors
	string name() { return inst_name; }
	vector<Net *> *getInputs() { return inputs; }
	Net* getOutput() { return output; }
	int getNumInputs() { return inputs->size(); }
	int getDelay() { return delay; }
 protected:
	vector<Net *> *inputs;
	Net *output;
	string inst_name;
	int delay;
};

class And : public Gate {
 public:
	And();
	And(string n) : Gate(n) {}
	And(string n, int d) : Gate(n, d) {}
//	~And();
	char eval();
	void dump(ostream &os);
};

class Or : public Gate {
 public:
	Or();
	Or(string n) : Gate(n) {}
	Or(string n, int d) : Gate(n, d) {}
//	~Or();
	char eval();
	void dump(ostream &os);
};

class Nor : public Gate {
 public:
	Nor();
	Nor(string n) : Gate(n) {}
	Nor(string n, int d) : Gate(n, d) {}
//	~Nor();
	char eval();
	void dump(ostream &os);
};

class Nand : public Gate {
 public:
	Nand();
	Nand(string n) : Gate(n) {}
	Nand(string n, int d) : Gate(n, d) {}
//	~Nand();
	char eval();
	void dump(ostream &os);
};

class Xor : public Gate {
 public:
	Xor();
	Xor(string n) : Gate(n) {}
	Xor(string n, int d) : Gate(n, d) {}
//	~Xor();
	char eval();
	void dump(ostream &os);
};

class Not : public Gate {
 public:
	Not();
	Not(string n) : Gate(n) {}
	Not(string n, int d) : Gate(n, d) {}
//	~Not();
	char eval();
	void dump(ostream &os);
};

#endif
