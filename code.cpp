/* FILE INFORMATION
File:     code.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the CODE class, which simulates reading instructions from the program
*/

#include "code.h"

  void Code::readCode(){

/*
    instruction_t instr;
    
    std::string inputString;
    std::string holderString;
    size_t pos = 0;

    ifstream file(codeFile, ios::in);
    if (file.is_open()){
      while (getline(file,inputString)){
        pos = inputString.find(" ");
        holderString = inputString.substr(0, pos);
        inputString.erase(0, pos + 1);
        instr.opcode = holderString;

        while ((pos = inputString.find(",")) != std::string::npos){
          holderString = inputString.substr(0, pos);
          inputString.erase(0, pos + 1);
          instr.operands.push_back(holderString);
        }

        instructions.push_back (instr);

        instr.opcode = "";
        instr.operands.clear();
      }
    }

*/
    //Read file line by line
    //Parse line into instruction_t
    //Put instruction_t generated into holder vector    
  }