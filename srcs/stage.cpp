/* FILE INFORMATION
File:     cpu.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the Stage class, which defines a cpu stage.
*/

#include <iostream>
#include "apex.h"
#include "stage.h"

Stage::Stage(std::string n, int l){
	latency = l;
	name = n;
	this->initialize();
}

//Reset the stage state
void Stage::initialize(){
	pc = 0;
	c = cycle;
	lcounter = latency;
	opcode = "NOP";
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
	if (!(empty)){
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
	//A stage should only advance if it is not empty, is ready,
	//and the destination is empty
	if (!this->empty && this->ready && dest.empty){
		//Copy fields from this stage to destination stage
		dest.pc = this->pc;
		dest.c = this->pc;
		dest.opcode = this->opcode;
		dest.lcounter = dest.latency;

		//Copy register fields
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

		//Set this stage's flags
		//this->isEmpty = true;
		//this->isReady = false;
		this->initialize();

		return true;
	}

	return false;
}

bool Stage::isEmpty(){
	return empty;
}

bool Stage::isReady(){

	if (ready && (latency == 0))
		return true;

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
