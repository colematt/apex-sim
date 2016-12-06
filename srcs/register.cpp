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

Registers::~Registers(){
	
}

//Initialize the RF with all registers/flags set to zero
//and all validities set to true
void Registers::initialize(){
  std::string reg_name;

  //Purge reg_file
  this->reg_file.clear();

  //Set general purpose register values and valids
  for (int r=0; r<num_reg; r++){
    reg_name = "P" + std::to_string(r);
    this->reg_file[reg_name] = std::make_tuple(0, true);
    this->free_list.push(reg_name); //Populate free list
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

//Create new instance of an R reg
std::string Registers::getRenamed(std::string archReg){
  std::string physReg = this->free_list.pop();
  std::string regHolder;

  this->front_end[physReg] = archReg;

  //Only update back_end if entry exists
  auto it = this->back_end.find(rReg);
  if (it != this->back_end.end()) {
    regHolder = std::get<0>(itt->second;
    this->back_end[rReg] = std::make_tuple(regHolder, false); //Set current to false
  } else 

  return physReg;
}

void Registers::commit(std::string pReg){
  std::string rReg;
  std::string prevReg;

  //Get R reg matched to P reg in front end list
  auto it = this->front_end.find(pReg);
  if (it != this->front_end.end()) {
    rReg = it->second;
  } else {
    std::string what_arg = reg + " is not a valid register";
    throw std::invalid_argument(what_arg);
  }

  //Get P reg matched to R reg in back end list
  auto itt = this->back_end.find(rReg);
  if (itt != this->back_end.end()) {
    prevReg = std::get<0>(itt->second;
    this->back_end[rReg] = std::make_tuple(pReg, true); //Set new P reg value
  } else {
    std::string what_arg = reg + " is not a valid register";
    throw std::invalid_argument(what_arg);
  }

  this->front_end[pReg] = ""; //Remove mapped R reg
  this->free_list.push(pReg); //Push P reg back into free list

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
int Registers::physRead(std::string reg){
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
bool Registers::physIsValid(std::string reg){
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

//Translate R reg to P reg to get value
//Throws std::invalid_argument exception if mapping doesn't exist
int Registers::read(std::string reg){
  int myvalue;
  std::string myReg

  auto it = this->back_end.find(reg);
  if (it != this->back_end.end()) {
    myReg = std::get<0>(it->second);
  } else {
    std::string what_arg = reg + " is not a valid register";
    throw std::invalid_argument(what_arg);
  }

  myvalue = physRead(myReg);

  return myvalue;
}

//Translate R reg to P reg to get validity
//Throws std::invalid_argument exception if mapping doesn't exist
bool Registers::isValid(std::string reg){
  bool myvalid;
  std::string myReg

  auto it = this->back_end.find(reg);
  if (it != this->back_end.end()) {
    myReg = std::get<0>(it->second);
  } else {
    std::string what_arg = reg + " is not a valid register";
    throw std::invalid_argument(what_arg);
  }

  myvalid = physIsValid(myReg);

  return myvalid;
}

void Registers::setNumReg(int num){
  if (num > 0)
    num_reg = 0;
}
