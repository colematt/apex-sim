/* FILE INFORMATION
File:     cpu.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the Stage class, which defines a cpu stage.
*/

#include <iostream>
#include "apex.h"
#include "stage.h"
#include "string.h"

Stage::Stage(std::string n, int l){
	latency = l;
	name = n;
	this->initialize();
}

//Reset the stage state
void Stage::initialize(){
	this.pc = pc;
	c = cycle;
	lcounter = latency;
	opcode = "";
	operands.clear();
	values.clear();
	values.resize(3, 0);
	valids.clear();
	valids.resize(3, false);
	empty = true;
	ready = false;
}

//Pretty print a Stage's contents
void Stage::display(){
	//Display the contents if the stage is not empty.
	if (!(this->isEmpty())){
		std::cout << name << ": " << opcode << " ";
		for(auto o : operands){
			std::cout << o << " ";
		}
		std::cout << std::endl;
	}
	//Otherwise, display an empty contents message
	else{
		std::cout << name << ": <empty>" << std::endl;
	}
}

//Advance a stage into destination stage, setting both Stages' flags
//(i.e. Destination is not empty, and not ready; Source is empty and not ready)
//If advancement is successful, return true
//If an error occurs, return false
bool Stage::advance(Stage &dest){
	//A source stage should only advance to a dest stage if:
	// 1. source stage is not empty,
	// 2. source stage is ready,
	// 3. dest stage is empty
	if (!this->isEmpty() && this->isReady() && dest.isEmpty()){
		//Copy fields from source stage to destination stage
		dest.pc = this->pc;
		dest.c = this->pc;
		dest.opcode = this->opcode;
		dest.lcounter = dest.latency;

		//Copy register fields from source stage to dest stage
		dest.operands.clear();
		for(auto op : this->operands){
			dest.operands.push_back(op);
		}
		dest.values.clear();
		for(auto v : this->values){
			dest.values.push_back(v);
		}
		dest.valids.clear();
		for(auto v : this->valids){
			dest.valids.push_back(v);
		}

		//Set destination stage's flags
		dest.empty = false;
		dest.ready = false;

		//Set source stage's flags
		//this->isEmpty = true;
		//this->isReady = false;
		this->initialize();

		return true;
	}

	// Failed to advance!
	return false;
}

//Flush the stage if its timestamp is later than <cycle> argument.
//Return true if a flush actually occurs, return false otherwise.
bool Stage::flush(int cycle, Registers &rf){
	//Check this stage's timestamp
	if (c > cycle){
		// This stage must be flushed.
		// Deallocate its physical register in the dest set
		if (opcode == "ADD" ||
				opcode == "SUB" ||
				opcode == "MOVC" ||
				opcode == "MUL" ||
				opcode == "AND" ||
				opcode == "OR" ||
				opcode == "EX-OR" ||
				opcode == "LOAD"){
						rf.deallocate(operands.at(0));
				}
		// Initialize() it, which also marks it empty.
		this->initialize();

		return true;
	}

	// A flush did not occur
	return false;
}

// Return whether this stage is occupied by an inflight instruction
bool Stage::isEmpty(){
	return empty;
}

// Return whether this stage is ready to be advanced because:
// 1. its work is complete (this.ready)
// 2. its latency is complete (ie MUL instructions)
bool Stage::isReady(){
	if (ready && (latency == 0))
		return true;
	else
	return false;
}

//Convert a string of the form "#(int)" to an int value
int Stage::littoi(std::string literal){
	literal = literal.erase(0,1);
	return std::stoi(literal);
}

//Return true if all valids are true
//Otherwise return false
bool Stage::isAllValid(){
	//A stage with no operands is always all valid (i.e. NOP or HALT)
	if (valids.empty())
		return true;
	//Otherwise check to see if all the valids are true,
	//returning false as soon as an invalid is found
	for(auto o : valids){
		if(!o)
			return false;
	}
	return true;
}
