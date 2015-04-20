# VerilogParserSimulator
This program parses and compiles a structural gate-level netlist in Verilog.
After compilation, the program will compute the final output based upon provided input values.

If any part of this documentation appears unclear, please don't hesitate to email me (public email).
Please put the name of the github repository in the subject.

See the following tutorial if you are unfamiliar with basics of digital logic:
http://www.facstaff.bucknell.edu/mastascu/elessonshtml/Logic/Logic1.html

The following 6 primitive logic gates are supported:
-and (2 inputs, 1 output)
-or (2 inputs, 1 output)
-nand (2 inputs, 1 output)
-nor (2 inputs, 1 output)
-xor (2 inputs, 1 output)
-not (1 input, 1 output)

A net with multiple drivers with different outputs is supported.

.v files are verilog files.

See the following tutorial if you are unfamiliar with verilog:
http://www.asic-world.com/verilog/veritut.html

.sim files are simulation files.
These files tell the program the input values of the digital circuit.
PI stands for Principal Input.
.sim files take on the following format:
PI1     PI2     ... PIn_val
PI1_val PI2_val ... PIn_val
.
.
.
PI1_val PI2_val ... PIn_val

.out files are output files.
These files are the results of the digital circuit's outputs.
PO stands for Principal Output.
t1, t2, ... tn stands for the time delay for each output.
.out files take on the following format:
PI1     PI2     ... PIn_val => PO1        PO2        ... POn
PI1_val PI2_val ... PIn_val => PO1_val@t1 PO2_val@t2 ... POn_val@tn
.
.
.
PI1_val PI2_val ... PIn_val => PO1_val@t1 PO2_val@t2 ... POn_val@tn

To build the program, type:
make
To run the program, type:
./gsim verilog_file input_sim_file output_sim_file
