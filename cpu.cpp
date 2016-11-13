/* FILE INFORMATION
File:     cpu.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the CPU class, which simulates operation of a five stage CPU.
*/

#include "cpu.h"

int Stage::littoi(std::string literal){
	literal = literal.erase(0,1);
	return std::stoi(literal);
}
