/* FILE INFORMATION
File:     code.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the CODE class, which simulates reading instructions from the program
*/

#include <fstream>
#include "code.h"

  Code::Code(const char* codeFile){
    this->readCode(codeFile);
  }

  void Code::readCode(const char* codeFile){

    Instruction::instruction_t instr;
    
    std::string inputString;
    std::string holderString;
    size_t pos = 0;

    std::ifstream file(codeFile);
    if (file.is_open()){
      while (getline(file,inputString)){

        //Get opcode
        pos = inputString.find(" ");
        holderString = inputString.substr(0, pos);
        inputString.erase(0, pos + 1);
        instr.opcode = holderString;

        //Get operands
        while ((pos = inputString.find(",")) != std::string::npos){
          holderString = inputString.substr(0, pos);
          inputString.erase(0, pos + 1);
          instr.operands.push_back(holderString);
        }

        Code::instructions.push_back (instr);

        instr.opcode = "";
        instr.operands.clear();
      }
    }   
  }

  //Get instruction given index of instruction pointer
  Instruction::instruction_t Code::getInstr(int addr){
    addr = addr - 4000;
    return instructions.at (addr);
  }