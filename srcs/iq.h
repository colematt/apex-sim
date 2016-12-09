/* FILE INFORMATION
File:     iq.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header file for iq.cpp
*/

#include "stage.h"
#include <string>
#include <deque>

#ifndef IQ_H
#define IQ_H

class IQ{
private:
	std::deque<Stage> issue_queue;

public:
	IQ();
	~IQ();

	bool isEmpty();

	void display();
	void initialize();

	//Add stage to Issue Queue to be issued on a later cycle
	void dispatchInst(Stage &stage);

	void updateSrc(std::string reg, int val);

	void issueInst();

	void flush(int cycle);
};

#endif
