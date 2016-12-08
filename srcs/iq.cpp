/* FILE INFORMATION
File:     iq.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the IQ class, which simulates the operation of a Instruction Queue.
*/

#include "iq.h"

IQ::IQ();

IQ::~IQ();

//Display the contents of the ROB
//Each row is cycle#, opcode of the contained sta
void ROB::display(){
	std::cout << "Cycle : Opcode"
	for (auto e : reorder_buffer){
		std::cout << e.c << " : " << e.opcode << endl;
	}
}

//Initialize the ROB to empty state
void ROB::initialize(){
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

void IQ::flush(int cycle);
