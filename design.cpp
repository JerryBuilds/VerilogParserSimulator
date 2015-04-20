// design.cpp

#include "design.h"

Design::Design()
{
	desname = "";
}

Design::Design(string n)
{
	desname = n;
}

Design::~Design()
{

	// use iterator to iterate through both maps to delete everything
	map<string, Net *>::iterator itNet;
	map<string, Gate *>::iterator itGate;

	for (itNet = designNets.begin(); itNet != designNets.end(); itNet++)
	{
		delete itNet->second;
	}

	for (itGate = designGates.begin(); itGate != designGates.end(); itGate++)
	{
		delete itGate->second;
	}

}

Net * Design::findNet(string net_name)
{
	if ( designNets.find(net_name) != designNets.end() )
		return designNets[net_name];
	else
		return NULL;
}

Gate * Design::findGate(string inst_name)
{
	if ( designGates.find(inst_name) != designGates.end() )
		return designGates[inst_name];
	else
		return NULL;
}

Net * Design::addFindNet(string n)
{
	if ( designNets.find(n) != designNets.end() )
		return designNets[n];
	else
	{
		Net * mynet = new Net(n);
		designNets[n] = mynet;
		return mynet;//or designNets[n]???
	}
}

Gate * Design::addFindGate(int gtype, string n)
{
	if ( designGates.find(n) != designGates.end() )
		return designGates[n];
	else
	{
		// account for different type of gates
		if ( gtype == AND )
		{
			Gate * mygate = new And(n,1);
			designGates[n] = mygate;
			return mygate;
		}
		else if ( gtype == OR )
		{
			Or * mygate = new Or(n,1);
			designGates[n] = mygate;
			return mygate;
		}
		else if ( gtype == NAND )
		{
			Nand * mygate = new Nand(n,1);
			designGates[n] = mygate;
			return mygate;
		}
		else if ( gtype == NOR )
		{
			Nor * mygate = new Nor(n,1);
			designGates[n] = mygate;
			return mygate;
		}
		else if ( gtype == XOR )
		{
			Xor * mygate = new Xor(n,1);
			designGates[n] = mygate;
			return mygate;
		}
		else
		{
			Not * mygate = new Not(n,1);
			designGates[n] = mygate;
			return mygate;
		}

	}

}

Gate * Design::addFindGate(int gtype, string n, int d)
{
	if ( designGates.find(n) != designGates.end() )
		return designGates[n];
	else
	{
		// account for different type of gates
		if ( gtype == AND )
		{
			Gate * mygate = new And(n,d);
			designGates[n] = mygate;
			return mygate;
		}
		else if ( gtype == OR )
		{
			Or * mygate = new Or(n,d);
			designGates[n] = mygate;
			return mygate;
		}
		else if ( gtype == NAND )
		{
			Nand * mygate = new Nand(n,d);
			designGates[n] = mygate;
			return mygate;
		}
		else if ( gtype == NOR )
		{
			Nor * mygate = new Nor(n,d);
			designGates[n] = mygate;
			return mygate;
		}
		else if ( gtype == XOR )
		{
			Xor * mygate = new Xor(n,d);
			designGates[n] = mygate;
			return mygate;
		}
		else
		{
			Not * mygate = new Not(n,d);
			designGates[n] = mygate;
			return mygate;
		}

	}

}

vector<Net *> * Design::getPINets()
{
	vector<Net *> * myvector = new vector<Net *>; // dynamically allocate a vector
	vector<string>::iterator it; // declare an iterator to iterate through principal inputs
	for (it = pis.begin(); it != pis.end(); it++)
	{
		myvector->push_back(designNets[*it]); // add the principal input to the vector
	}

	return myvector; // return the vector pointer
}

vector<Net *> * Design:: getPONets()
{
	vector<Net *> * myvector = new vector<Net *>; // dynamically allocate a vector
	vector<string>::iterator it; // declare an iterator to iterate through principal inputs

	for (it = pos.begin(); it != pos.end(); it++)
	{
		myvector->push_back(designNets[*it]); // add the principal input to the vector
	}

	return myvector; // return the vector pointer
}


vector<Net *> * Design::getWireNets()
{
	vector<Net *> * myvector = new vector<Net *>; // dynamically allocate a vector
	vector<string>::iterator check; // declare an iterator to check and exclude PIs and POs
	map<string, Net *>::iterator it; // declare an iterator to iterate through all nets

	// iterating through all nets
	for (it = designNets.begin(); it != designNets.end(); it++)
	{
		bool notJustWire = false;

		// check to see if the net is a PI
		// if net is PI, skip and do not add this net
		for (check = pis.begin(); check != pis.end(); check++)
		{
			if ( it->first == *check )
			{
				notJustWire = true;
				break;
			}
		}

		// check to see if the net is a PO
		// if net is PO, skip and do not add this net
		for (check = pos.begin(); check != pos.end(); check++)
		{
			if ( it->first == *check )
			{
				notJustWire = true;
				break;
			}
		}

		if ( notJustWire == true )
			continue;

		// finally, if the net is not a PI or PO,
		// add the net
		myvector->push_back(designNets[it->first]);
	}

	return myvector;
}

vector<Net *> * Design::getAllNets()
{
	vector<Net *> * myvector = new vector<Net *>; // dynamically allocate a vector
	map<string, Net *>::iterator it; // declare a map iterator to iterate through all elements

	for (it = designNets.begin(); it != designNets.end(); it++)
	{
		myvector->push_back(designNets[it->first]); // add the net to the vector
	}

	return myvector; // return the vector pointer
}

vector<Gate *> * Design::getAllGates()
{
	vector<Gate *> * myvector = new vector<Gate *>; // dynamically allocate a vector
	map<string, Gate *>::iterator it; // declare a map iterator to iterate through all elements

	for (it = designGates.begin(); it != designGates.end(); it++)
	{
		myvector->push_back(designGates[it->first]); // add the gate to the vector
	}

	return myvector; // return the vector pointer
}

void Design::dump(ostream &os)
{
	// for general use
	vector<string>::iterator it;
	vector<Net *>::iterator netIt;
	vector<Gate *>::iterator gateIt;

	// prints "module" and module name
	os << "module " << desname << "(";

	// prints all PIs in module
	for (it = pis.begin(); it != pis.end(); it++)
	{
		os << *it << ", ";
	}

	// prints all POs in module
	for (int i=0; i < pos.size(); i++)
	{
		os << pos[i];
		if ( (i+1) == pos.size() )
			break;
		os << ", ";
	}
	os << ");" << endl;
	
	// prints out a list of all PIs
	vector<Net *> * PINets = this->getPINets();
	for (netIt = PINets->begin(); netIt != PINets->end(); netIt++)
	{
		os << "\tinput " << (*netIt)->name() << ";" << endl;
	}

	// prints out a list of all POs
	vector<Net *> * PONets = this->getPONets();
	for (netIt = PONets->begin(); netIt != PONets->end(); netIt++)
	{
		os << "\toutput " << (*netIt)->name() << ";" << endl;
	}


	// prints out a list of all other wires
	vector<Net *> * WireNets = this->getWireNets();
	for (netIt = WireNets->begin(); netIt != WireNets->end(); netIt++)
	{
		os << "\twire " << (*netIt)->name() << ";" << endl;
	}


	// prints out a list of all gates and their nets
	vector<Gate *> * Gates = this->getAllGates();
	for (gateIt = Gates->begin(); gateIt != Gates->end(); gateIt++)
	{
		os << "\t";
		(*gateIt)->dump(os);
		os << endl;
	}


	// prints "endmodule"
	os << "endmodule";

	// cleanup
	delete PINets;
	delete PONets;
	delete WireNets;
	delete Gates;
	
}

bool Design::isPI(Net *n)
{
	string myname = n->name(); // this is the name to check
	vector<string>::iterator it; // declare an iterator to iterate through principal inputs

	for (it = pis.begin(); it != pis.end(); it++)
	{
		// check if the net is among the principal inputs
		if ( myname == *it )
			return true;
	}

	return false;
}

bool Design::isPO(Net *n)
{
	string myname = n->name(); // this is the name to check
	vector<string>::iterator it; // declare an iterator to iterate through principal outputs

	for (it = pos.begin(); it != pos.end(); it++)
	{
		// check if the net is among the principal outputs
		if ( myname == *it )
			return true;
	}

	return false;
}

vector<Net *> * Design::toposort()
{
	// iterators
	vector<Net *>::iterator nt;

	// make preparations for depth first search
	vector<Net *> * allNets = getAllNets();
	vector<Net *> * PONets = getPONets();
	vector<Net *> * orderList = new vector<Net *>;

	// initialize all values of map to unsearched
	map<string, int> netStatus;
	for (nt = allNets->begin(); nt != allNets->end(); nt++)
	{
		netStatus[(*nt)->name()] = WHITE;
	}


	// iterate through all outputs, and apply depth first search
	for (nt = PONets->begin(); nt != PONets->end(); nt++)
	{
		// apply DFS to figure out order
		dfs_visit(*nt, orderList, netStatus);

	}

	// cleanup
	delete allNets;
	delete PONets;


	return orderList;
	//***********************
	// don't forget to delete orderList later!!
	//***********************

}

void Design::dfs_visit(Net * n, vector<Net *> * finishedList, map<string, int> & colormap)
{
	// setup
	string netname = n->name();

	// base case 1:
	// if current net is already black,
	// leave immediately
	if ( colormap[netname] == BLACK )
		return;

	// base case 2:
	// if current net has no previous nets (is an input)
	// label current net as completely searched (black)
	// add current net to finished list
	if ( find( pis.begin(), pis.end(), netname ) != pis.end() )
	{
		colormap[netname] = BLACK;
		finishedList->push_back(n);
		return;
	}

	// more setup
	vector<Gate *>::iterator gt;
	vector<Net *>::iterator nt;
	vector<Gate *> * allDrivers = n->getDrivers();

	// label current net as touched (gray)
	// search all previous unsearched nets by calling own function
	// label current net as completely searched, children completely searched (black)
	// add current net to finished list
	colormap[netname] = GRAY;

	// iterate through all drivers of current net
	// hopefully each net only has one driver, but just in case...
	for (gt = allDrivers->begin(); gt != allDrivers->end(); gt++)
	{
		vector<Net *> * allInputs = (*gt)->getInputs();

		// iterate through all input nets of driver
		for (nt = allInputs->begin(); nt != allInputs->end(); nt++)
		{
			// recursively call self
			dfs_visit(*nt, finishedList, colormap);

		}

	}


	colormap[netname] = BLACK;
	finishedList->push_back(n);
	return;

}
