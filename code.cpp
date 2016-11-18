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
    
    std::string inputString;
    std::string holderString;
    size_t pos = 0;
    int i = 0;

    std::ifstream file(codeFile);
    if (file.is_open()){
      while (getline(file,inputString)){

      	//Remove '\r' character from end of string
      	inputString.erase(std::remove(inputString.begin(), inputString.end(), '\r'), inputString.end());

        //Get opcode
        pos = inputString.find(" ");
        holderString = inputString.substr(0, pos);
        inputString.erase(0, pos + 1);

        //On HALT, opcode was leaking into operands. If inputString and holderString equal
        //there are no opcode. Set inputString to " " to skip operand parsing.
        if(inputString == holderString) inputString = " ";

        Code::instructions.push_back(holderString);
        i++;

        //Get operands
        while ((pos = inputString.find(",")) != std::string::npos){
          holderString = inputString.substr(0, pos);
          inputString.erase(0, pos + 2);

          Code::instructions.push_back(holderString);
          i++;
        }

        //Get last operand after comma or if no commas.
        if (inputString != " "){
          Code::instructions.push_back(inputString);
          i++;
        }

        //Populate any open byte addressable positions for instruction
        while (i < 4){
          Code::instructions.push_back(" ");
          i++;
        }

        i = 0;
      }
    }   
  }

  //Get instruction given index of instruction pointer
  std::vector<std::string> Code::getInstr(int addr){
    std::vector<std::string> instr;

    //Modify incoming address to work with random access indexing of vector
    addr = addr - 4000;

    //Set opcode field for Instruction object
    instr.push_back(Code::instructions.at(addr));
    addr++;

    //Set operand fields for Instruction object if any
    for (int i = 0; i < 3; i++){
      instr.push_back(Code::instructions.at(addr));
      addr++;
    }

    //Return Instruction object for use by cpu
    return instr;
  }
  