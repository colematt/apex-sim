/* FILE INFORMATION
File:     code.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the CODE class, which simulates reading instructions from the program
*/

#include <fstream>
#include <string>
#include <algorithm>
#include "code.h"

  Code::Code(const char* codeFile){
    this->readCode(codeFile);
  }

  //Read contents of file into a vector of instruction_t
  void Code::readCode(const char* codeFile){

    Instruction instr;
    
    std::string inputString;
    std::string holderString;
    size_t pos = 0;

    std::ifstream file(codeFile);
    if (file.is_open()){
      while (getline(file,inputString)){

      	//Remove '\r' character from end of string
      	inputString.erase(std::remove(inputString.begin(), inputString.end(), '\r'), inputString.end());

        //Get opcode
        pos = inputString.find(" ");
        holderString = inputString.substr(0, pos);
        inputString.erase(0, pos + 1);
        instr.opcode = holderString;

        //Get operands
        while ((pos = inputString.find(",")) != std::string::npos){
          holderString = inputString.substr(0, pos);
          inputString.erase(0, pos + 2);
          instr.operands.push_back(holderString);
        }

        //Get land operand after comma or if no commas.
        if (inputString != " "){
          instr.operands.push_back(inputString);
        }

        Code::instructions.push_back (instr);

        instr.opcode = "";
        instr.operands.clear();
      }
    }   
  }

  //Get instruction given index of instruction pointer
  Instruction Code::getInstr(int addr){
    addr = addr - 4000;
    return Code::instructions.at (addr);
  }