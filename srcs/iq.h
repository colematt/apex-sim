/* FILE INFORMATION
File:     iq.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header file for iq.cpp
*/

#include <string>
#include <deque>
#include "register.h"
#include "stage.h"

#ifndef IQ_H
#define IQ_H

class IQ{
private:
	std::deque<Stage> issue_queue;

public:
	IQ();
	~IQ();

	// Interface functions
	void display();
	void initialize();

	// Utility functions
	bool isEmpty();
	void dispatchInst(Stage &stage);
	void updateSrc(std::string reg, int val);
	bool issue(Stage& ALU, Stage& MUL, Stage& LSFU, Stage& B);
	void flush(int cycle, Registers &rf);
	bool hasEntryWithOpcode(std::string oc);
};

#endif
