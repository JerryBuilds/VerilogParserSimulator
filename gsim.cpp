// Jerry Zhang
// Tianshi Zhang
// autoparse

#include <iostream>
#include <fstream>

#include "vlg_parser.h"
#ifdef AUTOPARSE
#include "vlg_parser_auto.h"
#else
#include "vlg_parser_man.h"
#endif

#include "design.h"
#include "gates.h"
#include "net.h"

#include "logicsim.h"

using namespace std;

int main(int argc, char *argv[])
{
	// check for 4 arguments
    if(argc < 4){
        cerr << "Usage: ./gsim verilog_file input_sim_file output_sim_file" << endl;
        return 1;
    }

#ifdef AUTOPARSE
    VlgParser *parser = new VlgParserAuto();
#else
    VlgParser *parser = new VlgParserMan();
#endif

	// declare Design object
    Design * blueprint = parser->parse(argv[1]);

	// output of parsing to verify functionality
    ofstream vfile("design.v"); // opens verilog output file
    blueprint->dump(vfile); // outputting the newly generated verilog file

	// start logic simulation
	LogicSim simulator(blueprint); // declare LogicSim class
    ifstream simInput(argv[2]); // open simulating input file
	ofstream simOutput(argv[3]); // opens simulating output file
	simulator.readIn(simInput); // reads the inputs into LogicSim
	simulator.calculate(); // calculates the outputs and delays in LogicSim
	simulator.writeOut(simOutput); // writes the outputs from LogicSim

	// cleanup
	delete parser;

	vfile.close();
	simInput.close();
	simOutput.close();


    return 0;
}
