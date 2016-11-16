/* FILE INFORMATION
File:     mmu.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header for code.cpp
*/
#ifndef CODE_H
#define CODE_H

#include <vector>
#include <string>

class Code{
private:
	std::vector<std::string> instructions;

public:
	//Instantiates a Code object given a file to read from
	Code(const char* codeFile);
	
	//Reads contents of file into a vector os strings
	void readCode(const char* codeFile);

	//Returns instruction object given instruction pointer value.
	//Object returns in 4 bytes starting at value given.
	std::vector<std::string> getInstr(int addr);

};
#endif
