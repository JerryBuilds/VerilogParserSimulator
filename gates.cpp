// gate.cpp

#include "gates.h"

using namespace std;

Gate::Gate()
{
	inst_name = "";
	delay = 1;
	inputs = new vector<Net *>;
}

Gate::Gate(string n)
{
	inst_name = n;
	delay = 1; // set default delay to 1
	inputs = new vector<Net *>;
}

Gate::Gate(string n, int d)
{
	inst_name = n;
	delay = d;
	inputs = new vector<Net *>;
}

Gate::~Gate()
{
/*
	// delete all input nets
	vector<Net *>::iterator it;

	for (it = inputs->begin(); it != inputs->end(); it++)
	{
		delete *it;
	}
*/
	delete inputs;
}

char And::eval()
{
	// if any input is '0', then output '0'
	// if none are '0' but some are 'X', then output 'X'
	// finally, if neither case, then output '1'

	char val;
	bool X_exists = false;
	vector<Net *>::iterator it;

	for (it = inputs->begin(); it != inputs->end(); it++)
	{
		val = (*it)->getVal();
		if ( val == '0' )
			return '0';
		if ( val == 'X' )
			X_exists = true;
	}

	if ( X_exists )
		return 'X';

	return '1';
}

void And::dump(ostream &os)
{
	os << "and " << "#" << delay << " ";
	os<< inst_name << "(";
	os << output->name() << ", ";
	for (int i=0; i < inputs->size(); i++)
	{
		os << inputs->at(i)->name();
		if ( (i+1) == inputs->size() )
			break;
		os << ", ";
	}
	os << ");";
}

char Or::eval()
{
	// if any input is '1', then output '1'
	// if none are '1' but some are 'X', then output 'X'
	// finally, if neither case, then output '0'

	char val;
	bool X_exists = false;
	vector<Net *>::iterator it;

	for (it = inputs->begin(); it != inputs->end(); it++)
	{
		val = (*it)->getVal();
		if ( val == '1' )
			return '1';
		if ( val == 'X' )
			X_exists = true;
	}

	if ( X_exists )
		return 'X';

	return '0';
}

void Or::dump(ostream &os)
{
	os << "or " << "#" << delay << " ";
	os<< inst_name << "(";
	os << output->name() << ", ";
	for (int i=0; i < inputs->size(); i++)
	{
		os << inputs->at(i)->name();
		if ( (i+1) == inputs->size() )
			break;
		os << ", ";
	}
	os << ");";
}

char Nor::eval()
{
	// effect opposite of Or
	// if any input is '1', then output '0'
	// if none are '1' but some are 'X', then output 'X'
	// finally, if neither case, then output '1'

	char val;
	bool X_exists = false;
	vector<Net *>::iterator it;

	for (it = inputs->begin(); it != inputs->end(); it++)
	{
		val = (*it)->getVal();
		if ( val == '1' )
			return '0';
		if ( val == 'X' )
			X_exists = true;
	}

	if ( X_exists )
		return 'X';

	return '1';
}

void Nor::dump(ostream &os)
{
	os << "nor " << "#" << delay << " ";
	os<< inst_name << "(";
	os << output->name() << ", ";
	for (int i=0; i < inputs->size(); i++)
	{
		os << inputs->at(i)->name();
		if ( (i+1) == inputs->size() )
			break;
		os << ", ";
	}
	os << ");";
}

char Nand::eval()
{
	// effect opposite of And
	// if any input is '0', then output '1'
	// if none are '0' but some are 'X', then output 'X'
	// finally, if neither case, then output '0'

	char val;
	bool X_exists = false;
	vector<Net *>::iterator it;

	for (it = inputs->begin(); it != inputs->end(); it++)
	{
		val = (*it)->getVal();
		if ( val == '0' )
			return '1';
		if ( val == 'X' )
			X_exists = true;
	}

	if ( X_exists )
		return 'X';

	return '0';
}

void Nand::dump(ostream &os)
{
	os << "nand " << "#" << delay << " ";
	os<< inst_name << "(";
	os << output->name() << ", ";
	for (int i=0; i < inputs->size(); i++)
	{
		os << inputs->at(i)->name();
		if ( (i+1) == inputs->size() )
			break;
		os << ", ";
	}
	os << ");";
}

char Xor::eval()
{
	// if there are any 'X', output 'X'
	// check if there is an odd number of '1'
	int counter = 0;
	vector<Net *>::iterator it;
	for (it = inputs->begin(); it != inputs->end(); it++)
	{
		if ( (*it)->getVal() == 'X' )
			return 'X';
		if ( (*it)->getVal() == '1' )
			counter++;
	}
	if ( counter % 2 == 1 )
		return '1';
	else
		return '0';
}

void Xor::dump(ostream &os)
{
	os << "xor " << "#" << delay << " ";
	os<< inst_name << "(";
	os << output->name() << ", ";
	for (int i=0; i < inputs->size(); i++)
	{
		os << inputs->at(i)->name();
		if ( (i+1) == inputs->size() )
			break;
		os << ", ";
	}
	os << ");";
}

char Not::eval()
{
	// the opposite of the input
	// if input is 'X', then also output 'X'
	// if there are multiple drivers and there are
	// conflicting values, output 'X'
	char prevVal, nextVal;

	prevVal = inputs->at(0)->getVal();
	for (int i=1; i < inputs->size(); i++)
	{
		nextVal = inputs->at(i)->getVal();
		if ( nextVal == 'X' )
			return 'X';
		if ( nextVal != prevVal )
			return 'X';
	}

	if ( prevVal == 'X' )
		return 'X';
	else if ( prevVal == '0' )
		return '1';
	else
		return '0';
	
}

void Not::dump(ostream &os)
{
	os << "not " << "#" << delay << " ";
	os<< inst_name << "(";
	os << output->name() << ", ";
	for (int i=0; i < inputs->size(); i++)
	{
		os << inputs->at(i)->name();
		if ( (i+1) == inputs->size() )
			break;
		os << ", ";
	}
	os << ");";
}
