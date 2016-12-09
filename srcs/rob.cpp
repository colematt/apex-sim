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

ROB::~ROB();

bool isEmpty(){
	return reorder_buffer.empty()
}

//Display the contents of the ROB
//Each row is cycle#, opcode of the contained stage
void ROB::display(){
	std::cout << "Cycle : Opcode";
	for (auto e : reorder_buffer){
		std::cout << e.c << " : " << e.opcode << endl;
	}
}

//Initialize the ROB to empty state
void ROB::initialize(){
	reorder_buffer.clear();
}

//Remove head from ROB and call registers' commit function,
//updating backend table and free list
void ROB::commit(Registers &reg){
	std::string pReg;
	pReg = this->reorder_buffer.front().operands.at(0);
	this->reorder_buffer.pop_front();
	reg.commit(pReg);
}

//Add a Stage instance to ROB
void ROB::addStage(Stage &stage){
	if (this->reorder_buffer.size() < this.max_size){
		this->reorder_buffer.push_back(stage);
	}
}

//Given a cycle value gets cycle value of current head
//and returns if they are equal (==)
bool ROB::match(Stage& stage){ //TODO update to hand stage being passed was int
	int size = 0;
	int passedCycle = 0;
	int headCycle = 0;

	size = this->reorder_buffer.size();
	passedCycle = stage.cycle;

	if(size > 0){
		headCycle = this->reorder_buffer.front().cycle;
	}

	if(headCycle == passedCycle){
		return true;
	}

	return false;
}

// Flush all entries in the ROB with whose cycle time stamp
// is >= specified time stamp (used when branch is taken)
void ROB::flush(int cycle){
		// ASSUMPTION: the entries in the IQ and ROB are
		// sorted at all times by their timestamp of creation (c)

		// Point an iterator at the start of the IQ
		std::deque<Stage>::const_iterator it = reorder_buffer.begin();

		// Traverse until encountering an entry
		// whose cycle timestamp indicates it must be flushed
		while(it->c < cycle){
			++it;
		}

		// flush the elements from the current iterator to end:
		reorder_buffer.erase(it, reorder_buffer.end());
}
