#ifndef LOGIC_SIM
#define LOGIC_SIM

#include "design.h"
#include <sstream>
#include <iomanip>

// to make it easier on readability
typedef vector<vector<char> * > simData;
typedef vector<vector<int> * > simDelay;

class LogicSim {
 public:

	LogicSim();
	LogicSim(Design * d);

	~LogicSim();

	// file i/o
	int readIn(ifstream & is);	// load up simInputs
								// load up simOrder
								// prepare simOutputs
								// check for errors
	void writeOut(ostream & os);// write out simOutputs

	// mutators
	void addInputVector(); // dynamically allocate new vector in simInputs
	void addInputVal(int index, char val); // add a value to simInputs
	void addOutputVector(); // dynamically allocate new vector in simOutputs
	void addOutputVal(int index, char val); // add a value to simOutputs
	void addDelayVector(); // dynamically allocate new vector
	void addDelayVal(int index, int val); // add a value to simDelay

	// accessors
	simData * getSimInputs() { return _simInputs; }
	simData * getSimOutputs() { return _simOutputs; }
	vector<string> * getSimInOrder() { return _simInOrder; }
	vector<string> * getSimOutOrder() { return _simOutOrder; }

	// retrieve index for input and output orderings
	int inOrderIndex(string name);
	int outOrderIndex(string name); // unnecessary?

	// perform calculations
	void calculate();

 private:
	Design _d; // Design class

	int _inputSize;
	int _outputSize;

	simData * _simInputs; // simulation data of inputs
	simData * _simOutputs; // simulation data of outputs
	simDelay * _simDelay; // simulation delay
	vector<string> * _simInOrder; // order of inputs
	vector<string> * _simOutOrder; // order of outputs
	
};

#endif
