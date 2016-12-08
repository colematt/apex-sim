/* FILE INFORMATION
File:     iq.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the IQ class, which simulates the operation of a Instruction Queue.
*/

#include "iq.h"

IQ::IQ();

IQ::~IQ();

//Display the contents of the IQ
//Each row is cycle#, opcode of the contained stage
void IQ::display(){
	std::cout << "Cycle : Opcode"
	for (auto e : reorder_buffer){
		std::cout << e.c << " : " << e.opcode << endl;
	}
}

//Initialize the IQ to empty state
void IQ::initialize(){
	reorder_buffer.clear();
}

void IQ::dispatchInst(Stage &stage){
	this->issue_queue.push_back(stage);
}

void IQ::updateSrc(std::string reg, int val){
	if (issue_queue.size() > 0){
		for (Element& e : issue_queue){
			if(e.operands.at(1) == reg){
				e.values.at(1) = val;
				e.valids.at(1) = true;
			}
			if(e.operands.at(2) == reg){
				e.values.at(2) = val;
				e.valids.at(2) = true;
			}
		}
	}
}

// Flush all entries in the IQ with whose cycle time stamp
// is >= specified time stamp (used when branch is taken)
void IQ::flush(int cycle){
	// ASSUMPTION: the entries in the IQ and ROB are
	// sorted at all times by their timestamp of creation (c)

	// Point an iterator at the start of the IQ
	std::deque<int>::const_iterator it = issue_queue.begin();

	// Traverse until encountering an entry
	// whose cycle timestamp indicates it must be flushed
	while(it->c < cycle){
		++it;
	}

	// flush the elements from the current iterator to end:
	issue_queue.erase(it, issue_queue.end());
}
