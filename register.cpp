/* FILE INFORMATION
File:     register.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the Registers class, which simulates operation of a register file.
*/

#include "register.h"

Registers::Registers(){
  this->initialize();
}

//Initialize the RF with all registers/flags set to zero
//and all validities set to true
void Registers::initialize(){
  std::string reg_name;

  //Set general purpose register values and valids
  for (int r=0; r<NUM_REGS; r++){
    reg_name = "R" + std::to_string(r);
    this->reg_file[reg_name] = std::make_tuple(0, true);
  }

  //Set flag and special register values and valids
  this->reg_file["X"] = std::make_tuple(0, true);
  this->reg_file["Z"] = std::make_tuple(0, true);
}

//Display the contents of the registers/flags
void Registers::display(){
  std::string myname = "";
  int myvalue = 0;
  bool myvalid = true;
  
  for (auto it = this->reg_file.begin(); it != this->reg_file.end(); ++it) {
    myname = it->first;
    std::tie(myvalue, myvalid) = it->second;
    std::cout << myname << ": " << myvalue << "," << myvalid << std::endl;
  }
}

//Set reg_file[register] = (value,valid)
//Throws std::invalid_argument exception if register doesn't exist
void Registers::write(std::string reg, int value, bool valid){
  auto it = this->reg_file.find(reg);
  if (it != this->reg_file.end()){
    this->reg_file[reg] = std::make_tuple(value, valid);
  } else {
    std::string what_arg = reg + " is not a valid register";
    throw std::invalid_argument(what_arg);
  }
}

//Get reg_file[register] value
//Throws std::invalid_argument exception if register doesn't exist
int Registers::read(std::string reg){
  int myvalue;

  auto it = this->reg_file.find(reg);
  if (it != this->reg_file.end()) {
    myvalue = std::get<0>(it->second);
  } else {
    std::string what_arg = reg + " is not a valid register";
    throw std::invalid_argument(what_arg);
  }
  return myvalue;
}

//Check reg_file[register] validity
//Throws std::invalid_argument exception if register doesn't exist
bool Registers::isValid(std::string reg){
  bool myvalid;
  auto it = this->reg_file.find(reg);
  if (it != this->reg_file.end()) {
    myvalid = std::get<1>(it->second);
  } else {
    std::string what_arg = reg + " is not a valid register";
    throw std::invalid_argument(what_arg);
  }

  return myvalid;
}
