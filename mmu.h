/* FILE INFORMATION
File:     mmu.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header for mmu.cpp
*/

struct instruction_t {
    std::string opcode;
    std::vector<std::string> operands;
}

//TODO Make vector to hold instruction_t
//TODO Make vector of 32-bit integers to hold memory
