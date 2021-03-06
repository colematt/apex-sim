/* FILE INFORMATION
File:     register.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the Registers class, which simulates operation of a register file.
*/

#include "register.h"
#include "apex.h"

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

  //Flush free list
  std::deque<std::string> flush_list;
  free_list = flush_list;

  //Set general purpose register values and valids
  for (int r=0; r< (num_reg); r++){
    reg_name = "P" + std::to_string(r);
    this->reg_file[reg_name] = std::make_tuple(0, true);
    this->free_list.push_back(reg_name); //Populate free list
  }

  //Set flag and special register values and valids
  this->reg_file["X"] = std::make_tuple(0, true);
}

void Registers::dUrf(){
  std::string myname = "";
  std::string myRname = "";
  int myvalue = 0;
  bool myvalid = true;
  std::string holder = "";

  if (VERBOSE >= 1){
    std::cout << "Register : Value,Valid;Status" << std::endl;
  }
  
  for (auto it = this->reg_file.begin(); it != this->reg_file.end(); ++it) {
    myname = it->first;
    if (myname != "X"){
      std::tie(myvalue, myvalid) = it->second;
      std::cout << myname << ": " << myvalue << "," << myvalid << ";";

      for (auto itt = this->back_end.begin(); itt != this->back_end.end(); ++itt) {
        if (itt->second == myname){
          holder = "Committed";
        }
      }

      if (holder == ""){
        for (auto itt = this->front_end.begin(); itt != this->front_end.end(); ++itt) {
          if (itt->first == myname){
            holder = "Allocated";
          }
        }
      }

        
      for (auto fl = free_list.begin(); fl != this->free_list.end(); ++fl){
        if (*fl == myname){
          holder = "Free";
        }
      }
      std::cout << holder << std::endl;
    }
    holder = "";
  }
  holder = "";
}

void Registers::dMap(){
  std::string reg1 = "";
  std::string reg2 = "";

  if (VERBOSE >= 1){
    std::cout << "Physical : Architectural" << std::endl;
  }

  std::cout << "Front End Rename Table" << std::endl;
  for (auto it = this->front_end.begin(); it != this->front_end.end(); ++it){
    reg1 = it->first;
    reg2 = it->second;

    std::cout << reg1 << " : " << reg2 << std::endl;
  }

  if (VERBOSE >= 1){
    std::cout << "Architectural : Physical" << std::endl;
  }

  std::cout << "Back End Rename Table" << std::endl;
  for (auto it = this->back_end.begin(); it != this->back_end.end(); ++it){
    reg1 = it->first;
    reg2 = it->second;

    std::cout << reg1 << " : " << reg2 << std::endl;
  }
}

//Create new instance of an R reg
std::string Registers::getRenamed(std::string rReg){
  std::string physReg;
  std::string regHolder;

  physReg = this->free_list.front();
  this->free_list.pop_front();

  //Update or insert pReg value with physReg as key and archReg as value
  this->front_end[physReg] = rReg;
  this->reg_file[physReg] = std::make_tuple(0, false);

  //Check back end to see if there is commited value for R reg
  //If there is one set mapped P reg valid to false
  auto it = this->back_end.find(rReg);
  if (it != this->back_end.end()) {
    regHolder = it->second;
  }

  return physReg;
}

//Commit new value to R reg
void Registers::commit(std::string pReg){
  std::string rReg;
  std::string prevReg;

  //Get R reg matched to P reg in front end list
  auto it = this->front_end.find(pReg);
  if (it != this->front_end.end()) {
    rReg = it->second;
  } else {
    std::string what_arg = pReg + " is not a valid register";
    throw std::invalid_argument(what_arg);
  }

  auto itt = this->back_end.find(rReg);
  if (itt != this->back_end.end()){
    prevReg = itt->second;

    auto ittt = this->front_end.find(prevReg);
    if (ittt != this->front_end.end()){
      this->front_end.erase(ittt);
      this->free_list.push_back(prevReg);
      std::sort(free_list.begin(), free_list.end(), compareString);
    }
  }
  
  this->back_end[rReg] = pReg; //Set new P reg value

}

bool Registers::deallocate(std::string reg){
  if (reg[0] == 'R' || reg[0] == 'X'){
    return false;
  } else {
    auto it = this->front_end.find(reg);
    if (it != this->front_end.end()){
      this->front_end.erase(it); //Remove rename entry from front end table
      this->free_list.push_back(reg);
      std::sort(free_list.begin(), free_list.end(), compareString);
      return true;

    } else {
      return false;
    }
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
int Registers::read(std::string reg){
  int myvalue;
  std::string myReg;

  auto it = this->back_end.find(reg);
  if (it != this->back_end.end()) {
    myReg = (it->second);
    myvalue = physRead(myReg);
  } else {
    myvalue = 0;
  }

  return myvalue;
}

//Translate R reg to P reg to get validity
//Throws std::invalid_argument exception if mapping doesn't exist
bool Registers::isValid(std::string reg){
  bool myvalid;
  std::string myReg;

  auto it = this->back_end.find(reg);
  if (it != this->back_end.end()) {
    myReg = (it->second);
    myvalid = physIsValid(myReg);
  } else {
    myvalid = false;
  }

  return myvalid;
}

void Registers::setNumReg(int num){
  if (num > 0)
    num_reg = 0;
}

std::string Registers::translateReg(std::string pReg){
  std::string rReg = "";
  auto it = this->front_end.find(pReg);
  if (it != this->front_end.end()) {
    rReg = (it->second);
  } else {
    rReg = "";
  }
  return rReg;
}
