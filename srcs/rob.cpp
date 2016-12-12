/* FILE INFORMATION
File:     rob.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the ROB class, which simulates the operation of a Reorder Buffer.
*/

#include <iostream>
#include "rob.h"

ROB::ROB(){
	this->initialize();
}

ROB::~ROB(){}

//Display the contents of the ROB
//Each entry is a Stage, so we delegate the display call
void ROB::display(){
	std::cout << "Head" << std::endl;
	for (auto e : reorder_buffer){
		e.display();
	}
	std::cout << "Tail" << std::endl;
}

//Initialize the ROB to empty state
void ROB::initialize(){
	reorder_buffer.clear();
}

bool ROB::isEmpty(){
	return reorder_buffer.empty();
}

//Remove head from ROB and call registers' commit function,
//updating backend table and free list
void ROB::commit(Registers &reg){
	std::string curOpcode = this->reorder_buffer.front().opcode;
	if (curOpcode != "STORE" &&
		curOpcode != "BZ" &&
		curOpcode != "BNZ" &&
		curOpcode != "BAL" &&
		curOpcode != "JUMP"){
		std::string pReg;
		pReg = this->reorder_buffer.front().operands.at(0);
		reg.commit(pReg);
	}
	this->reorder_buffer.pop_front();
}

//Add a Stage instance to ROB
bool ROB::addStage(Stage &stage){
	if (this->reorder_buffer.size() < this->max_size){
		this->reorder_buffer.push_back(stage);
		return true;
	}
	return false;
}

//Given a cycle value gets cycle value of current head
//and returns if they are equal (==)
bool ROB::match(Stage& stage){
	// If stage is empty, it cannot match the ROB head entry!
	if (stage.isEmpty())
		return false;

	int size = 0;
	int passedCycle = 0;
	int headCycle = 0;

	size = this->reorder_buffer.size();
	passedCycle = stage.c;

	if(size > 0){
		headCycle = this->reorder_buffer.front().c;
	}

	if(headCycle == passedCycle){
		return true;
	}

	return false;
}

// Flush all entries in the ROB with whose cycle time stamp
// is >= specified time stamp (used when branch is taken)
// ASSUMPTION: the entries in the IQ and ROB are
// sorted at all times by their timestamp of creation (c)
void ROB::flush(int cycle){
		// Point an iterator at the start of the IQ
		std::deque<Stage>::iterator it = this->reorder_buffer.begin();

		// Traverse until encountering an entry
		// whose cycle timestamp indicates it must be flushed
		while(it->c < cycle){
			++it;
		}

		// flush the elements from the current iterator to end:
		this->reorder_buffer.erase(it, reorder_buffer.end());
}
