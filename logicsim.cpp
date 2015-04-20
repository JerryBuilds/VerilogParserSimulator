#include "logicsim.h"

LogicSim::LogicSim()
{
	// initialization
	_simInputs = new simData;
	_simOutputs = new simData;
	_simDelay = new simDelay;
	_simInOrder = new vector<string>;
	_simOutOrder = new vector<string>;
}

LogicSim::LogicSim(Design * d)
{
	// initialization
	_d = *d;
	_simInputs = new simData;
	_simOutputs = new simData;
	_simDelay = new simDelay;
	_simInOrder = new vector<string>;
	_simOutOrder = new vector<string>;

	vector<Net *> * PINets = _d.getPINets();
	_inputSize = PINets->size();
	delete PINets;

	vector<Net *> * PONets = _d.getPONets();
	_outputSize = PONets->size();
	delete PONets;
}

LogicSim::~LogicSim()
{
	// iterators
	simData::iterator st;
	simDelay::iterator dt;

	for (st = _simInputs->begin(); st != _simInputs->end(); st++)
	{
		delete *st;
	}
	delete _simInputs;

	for (st = _simOutputs->begin(); st != _simOutputs->end(); st++)
	{
		delete *st;
	}
	delete _simOutputs;

	for (dt = _simDelay->begin(); dt != _simDelay->end(); dt++)
	{
		delete *dt;
	}
	delete _simDelay;

	delete _simInOrder;
	delete _simOutOrder;

}

int LogicSim::readIn(ifstream & is)
{
	// preparations
	string mystring;
	string line;
	stringstream ss;
	char mychar;

	// first line
	// read in first line
	getline(is, line);
	ss << line << endl;

	// determine the number of inputs
	// setup _simInOrder

	ss >> mystring; // read in the first string

	// this while loop will continue to read in strings from the line
	// until there are no more strings to read in.
	// stringstream as a boolean function evaluates to false
	// when the read-in fails (in this case, when there are no more strings)
	while ( ss ) // while there are still strings to read in
	{
		_simInOrder->push_back(mystring); // add the string to simInOrder

		ss >> mystring; // read in the next string
	}

	// setup _inputSize
	_inputSize = _simInOrder->size();

	int counter = 0;
	getline(is, line); // read in the first combination
	ss.clear();
	ss << line << endl; // put the first combination into stringstream
	while ( is ) // while there are still lines to read
	{
		addInputVector(); // add a vector to simInputs
		ss >> mystring; // read in the first char
		mychar = mystring[0];
		while ( ss ) // while there are still chars to read
		{
			addInputVal(counter, mychar); // add value to the nth vector of simInputs
			ss >> mystring; // read in next char
			mychar = mystring[0];
		}
		counter++; // increase the index value
		getline(is, line); // read in the next line
		ss.clear();
		ss << line << endl;
	}


        //Error checking
    /*a) A specified PI on the first line does not exist in the design
    b) The number of input values for a vector does not match the number of PIOs specified on the first line
    c) An input value is not in the set {'0', '1', 'X'}

    */
    for(int i=0; i<_simInOrder->size(); i++){
        bool flag=false;
		vector<Net *> * PINets = _d.getPINets();
		int size = PINets->size();
        for(int j=0; j<size; j++){
            //cout<<(*_simInOrder)[i]<<endl;
            //cout<<((*(_d.getPINets()))[j])->name()<<endl;
            if((*_simInOrder)[i]==PINets->at(j)->name()){
                flag=true;
                break;
            }
        }
		delete PINets;
        if(flag==false){
            cout<<"Error: A specified PI on the first line does not exist in the design"<<endl;
            exit(0);
        }
    }
//    cout<<"Every PI in the simulation file exists in the design"<<endl;

    for(int i=0; i<_simInputs->size(); i++){
        if((*_simInputs)[i]->size()!=_simInOrder->size()){
            cout<<"Error: The number of input values for a vector does not match the number of PIOs specified on the first line"<<endl;
            cout<<"Line number: "<<i+1<<endl;
            exit(0);
        }
    }
//    cout<<"In every test case, every input net is given a test value"<<endl;

    for(int i=0; i<_simInputs->size(); i++){
        for(int j=0; j<_simInOrder->size(); j++){
            if((*((*_simInputs)[i]))[j]=='0') continue;
            if((*((*_simInputs)[i]))[j]=='1') continue;
            if((*((*_simInputs)[i]))[j]=='X') continue;
            cout<<"Error: An input value is not in the set {'0', '1', 'X'}"<<endl;
            cout<<"Line number: "<<i+1<<endl;
            exit(0);
        }
    }
//    cout<<"All test input values are either '0', '1', or 'X'"<<endl;
    cout<<"No errors for the test simulation file!"<<endl;
	return 0;
}

void LogicSim::writeOut(ostream &os)
{
	// preparations
	vector<string>::iterator st;
	vector<char>::iterator ct;
	simData::iterator it;
	string mystring;
	vector<int> inputSpaces; // keep track of how many spaces per input
	vector<int> outputSpaces; // keep track of how many spaces per output


	// first line

	// inputs
	for (st = _simInOrder->begin(); st != _simInOrder->end(); st++)
	{
		mystring = *st;
		inputSpaces.push_back(mystring.size());
		os << mystring << " ";
	}
	os << "==> ";

	// outputs
	for (st = _simOutOrder->begin(); st != _simOutOrder->end(); st++)
	{
		mystring = *st;
		int size = mystring.size();
		if ( size > 4 ) // default size 4 (to account for double digit delay)
		{
			outputSpaces.push_back(size);
			os << mystring << " ";
		}
		else
		{
			outputSpaces.push_back(4);
			os << setw(4) << left << mystring;
			os << " ";
		}
	}
	os << endl;

	// each successive line
	int counter = 0; // for inputs and delays
	for (it = _simOutputs->begin(); it != _simOutputs->end(); it++)
	{
		// inputs
		for (int i=0; i < _inputSize; i++)
		{
			char mychar = _simInputs->at(counter)->at(i);
			os << setw(inputSpaces[i]) << mychar;
			os << " ";
		}

		os << "==> ";

		// outputs
		for (int i=0; i < _outputSize; i++)
		{
			char mychar = _simOutputs->at(counter)->at(i);
			int mydelay = _simDelay->at(counter)->at(i);
			os << mychar << "@" << setw(outputSpaces[i]-2) << mydelay;
			os << " ";
		}

		os << endl;

		counter++;
	}

}

void LogicSim::addInputVector()
{
	vector<char> * myvector = new vector<char>;
	_simInputs->push_back(myvector);
}

void LogicSim::addInputVal(int index, char val)
{
	_simInputs->at(index)->push_back(val);
}

void LogicSim::addOutputVector()
{
	vector<char> * myvector = new vector<char>;
	_simOutputs->push_back(myvector);
}

void LogicSim::addOutputVal(int index, char val)
{
	_simOutputs->at(index)->push_back(val);
}

void LogicSim::addDelayVector()
{
	vector<int> * myvector = new vector<int>;
	_simDelay->push_back(myvector);
}

void LogicSim::addDelayVal(int index, int val)
{
	_simDelay->at(index)->push_back(val);
}

int LogicSim::inOrderIndex(string name)
{
	for (int i=0; i < _inputSize; i++)
	{
		if ( name == _simInOrder->at(i) )
			return i;
	}

	// if none exists
	return -1;
}


// retrieve computation order from Design class
// load up all input combinations to Design class
// calculate outputs, store them
void LogicSim::calculate()
{
//cout << "in calculate function" << endl;
	// iterators
	simData::iterator st;
	vector<char>::iterator ct;
	vector<string>::iterator gt;
	vector<Net *>::iterator it;

	// preparation
	vector<Net *> * evalOrder = _d.toposort(); // computation order
	vector<Net *> * PINets = _d.getPINets(); // inputs
	vector<Net *> * PONets = _d.getPONets(); // outputs
//cout << "done with prep" << endl;
	// setup order for output
	for (it = PONets->begin(); it != PONets->end(); it++)
	{
		_simOutOrder->push_back((*it)->name());
	}
//cout << "setup the order for output" << endl;

	// counter to keep track of output
	int counter = 0;

	// iterate through each input combination
	// each vector in simInputs is a different input combination
	for (st = _simInputs->begin(); st != _simInputs->end(); st++)
	{
		vector<char> * currentList = *st;

		// iterate through each principal input
		// load them up with input values
		for (it = PINets->begin(); it != PINets->end(); it++)
		{
			// determine which index this net corresponds to
			int index = this->inOrderIndex((*it)->name());
//cout << "index = " << index << endl;

			// add the list's nth index to the net's input
			(*it)->setVal(currentList->at(index));

		}
//cout << "out of loading zone" << endl;

		// perform computation
		for (it = evalOrder->begin(); it != evalOrder->end(); it++)
		{
			char val = (*it)->computeVal();
			(*it)->setVal(val);
//cout << (*it)->name() << " = " << (*it)->getVal() << endl;
			int delay = (*it)->computeDelay();
			(*it)->setDelay(delay);
		}


		// add output and delay values to simOutputs
		addOutputVector();
		addDelayVector();
		for (it = PONets->begin(); it != PONets->end(); it++)
		{
			addOutputVal(counter, (*it)->getVal());
			addDelayVal(counter, (*it)->getDelay());
		}

		counter++;

	}


	// cleanup
	delete PONets;
	delete PINets;
	delete evalOrder;

}
