/* FILE INFORMATION
File:     rob.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header file for rob.cpp
*/

#include "stage.h"
#include "register.h"
#include <deque>

#ifndef ROB_H
#define ROB_H

class ROB{
private:
	int max_size = 40;
	std::deque<Stage> reorder_buffer;

public:
	ROB();
	~ROB();

	//Interface functions
	void display();
	void initialize();

	//Utility functions
	bool isEmpty();
	void commit(Registers &reg);
	bool addStage(Stage &stage);
	bool match(Stage& stage);
	void flush(int cycle);
};

#endif
