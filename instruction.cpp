/* FILE INFORMATION
File:     mmu.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header for mmu.cpp
*/
#include <iostream>
#include <string>

//Convert a literal string (e.g. #16 or #-20) to an integer(e.g. 16, -20)
int Instruction::littoi(std::string literal){
	literal = literal.erase(0,1);
	return std::stoi(literal);
}
