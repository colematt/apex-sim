/* FILE INFORMATION
File:     rob.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the ROB class, which simulates the operation of a Reorder Buffer.
*/

#include "rob.h"

ROB::ROB();

ROB::~ROB();

void ROB::commit();

void ROB::addStage(Stage &stage){
	this->reorder_buffer.push(stage);
}

bool ROB::headReady(int cycle); //TODO compares cycle value passed to cycle value of head element
