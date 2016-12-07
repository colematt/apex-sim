/* FILE INFORMATION
File:     rob.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header file for rob.cpp
*/

#include "stage.h"
#include <queue>

#ifndef ROB_H
#define ROB_H
#define MAX = 40

class ROB{
private:

	std::queue<Stage> reorder_buffer;

public:
	ROB();
	~ROB();
	void commit();
	void addStage(Stage &stage); //Add new stage object to reorder buffer
								 //Stage comes from simulate.cpp through a function in stage.cpp (advance)
	bool headReady(int cycle); //Return if head matches cycle value passed
};

#endif
