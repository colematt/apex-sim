/* FILE INFORMATION
File:     rob.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header file for rob.cpp
*/

#include "stage.h"
#include "register.h"
#include <queue>

#ifndef ROB_H
#define ROB_H

class ROB{
private:
	int max_size = 40;
	std::queue<Stage> reorder_buffer;

public:
	ROB();
	~ROB();

	//Remove head from ROB and
	//call registers' commit function,
	//updating backend table and free list
	void commit(Registers &reg);

	//Add new stage object to reorder buffer
	//Stage comes from simulate.cpp through a function in stage.cpp (advance)
	void addStage(Stage &stage);

	//Check if head matches the cycle value passed
	bool headMatch(int cycle);
};

#endif
