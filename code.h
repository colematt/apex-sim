/* FILE INFORMATION
File:     mmu.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header for code.cpp
*/
#ifndef CODE_H
#define CODE_H

#include <vector>
#include "instruction.h"

class Code{
private:
	std::vector<Instruction>  instructions;

public:
	//Instantiates a Code object given a file to read from
	Code(const char* codeFile);
	
	//Reads contents of file into a vector
	void readCode(const char* codeFile);

	//Returns instruction given instruction point value.
	Instruction getInstr(int addr);

};
#endif