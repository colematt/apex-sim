/* FILE INFORMATION
File:     iq.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the IQ class, which simulates the operation of a Instruction Queue.
*/

#include <iostream>
#include "iq.h"

IQ::IQ(){
	this->initialize();
}

IQ::~IQ(){

}

// Return true if the IQ is empty,
// Return false otherwise
// (Delegates to stl::queue::empty())
bool IQ::isEmpty(){
	return issue_queue.empty();
}

//Display the contents of the IQ
//Each entry is a Stage, so we delegate the display logic
void IQ::display(){
	std::cout << "Head" << std::endl;
	for (auto e : issue_queue){
		e.display();
	}
	std::cout << "Tail" << std::endl;
}

//Initialize the IQ to empty state
void IQ::initialize(){
	issue_queue.clear();
}

//Dispatch an instruction to IQ
void IQ::dispatchInst(Stage &stage){
	stage.empty = false;
	stage.ready = false;
	this->issue_queue.push_back(stage);
}

//Forward the value of an R reg that was computed from an FU
//If an instruction is found to have an R reg that is being forwarded
//Set value and valid bit for associated operand fields
void IQ::updateSrc(std::string reg, int val){
	if (issue_queue.size() > 0){
		for (auto& e : issue_queue){

			//Handle forward to arithmatic instructions in IQ
			if(e.opcode == "ADD" ||
				e.opcode == "SUB" ||
				e.opcode == "MUL" ||
				e.opcode == "AND" ||
				e.opcode == "OR" ||
				e.opcode == "EX-OR"){
				if(e.operands.at(1) == reg){
					e.values.at(1) = val;
					e.valids.at(1) = true;
				}
				if(e.operands.at(2) == reg){
					e.values.at(2) = val;
					e.valids.at(2) = true;
				}
			}

			//Handle forward to LOAD instruction in IQ
			if(e.opcode == "LOAD"){
				if(e.operands.at(1) == reg){
					e.values.at(1) = val;
					e.valids.at(1) = true;
				}
			}

			//Handle forward to branch instructions in IQ
			if(e.opcode == "BAL" ||
				e.opcode == "JUMP"){
				if(e.operands.at(0) == reg){
					e.values.at(0) = val;
					e.valids.at(0) = true;
				}
			}

			//Handle forward to STORE instructions in IQ
			if(e.opcode == "STORE"){
				if(e.operands.at(0) == reg){
					e.values.at(0) = val;
					e.valids.at(0) = true;
				}
				if(e.operands.at(1) == reg){
					e.values.at(1) = val;
					e.valids.at(1) = true;
				}
			}
		}
	}
}

//TODO
bool issue(Stage* ALU, Stage* MUL, Stage* LSFU, Stage* B){
	//for (auto& e : issue_queue){
	for (auto i = this->issue_queue.begin(); i != this->issue_queue.end();)
		if (i->isReady()){
			if(i->opcode == "ADD" ||
				i->opcode == "SUB" ||
				i->opcode == "AND" ||
				i->opcode == "OR" ||
				i->opcode == "EX-OR" ||
				i->opcode == "MOV"){

				i->advance(ALU);
				return true;
			}

			if(i->opcode == "MUL"){
				
				return true;
			}

			if(i->opcode == "LOAD" ||
				i->opcode == "STORE"){

				return true;
			}

			if(i->opcode == "BAL" ||
				i->opcode == "JUMP" ||
				i->opcode == "BZ" ||
				i->opcode == "BNZ"){

				return true;
			}
		else{
			++i;
		}

		}
	}
	//Failed to issue instruction
	return false;
}

//TODO
//void checkReady(){}

// Flush all entries in the IQ with whose cycle time stamp
// is >= specified time stamp (used when branch is taken)
void IQ::flush(int cycle){
	// ASSUMPTION: the entries in the IQ and ROB are
	// sorted at all times by their timestamp of creation (c)

	// Point an iterator at the start of the IQ
	std::deque<Stage>::iterator it = issue_queue.begin();

	// Traverse until encountering an entry
	// whose cycle timestamp indicates it must be flushed
	while(it->c < cycle){
		++it;
	}

	// flush the elements from the current iterator to end:
	issue_queue.erase(it, issue_queue.end());
}
