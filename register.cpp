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
    this.reg_file[reg_name] = std::make_tuple(0, true)
  }

  //Set flag and special register values and valids
  this.reg_file["X"] = std::make_tuple(0, true);
  this.reg_file["Z"] = std::make_tuple(0, true);
}

//Display the contents of the registers/flags
void Registers::display(){
  std::string myname = "";
  int myvalue = 0;
  bool myvalid = true;

  std::cout << "Register File and Flags:" << endl;
  for (auto it = this.reg_file.begin(); it != this.reg_file.end(); ++it) {
    myname = it->first;
    std::tie(myvalue, myvalid) = it->second;
    std::cout << myname << ": " << myvalue << "," << myvalid << std::endl;
  }
}

//Set reg_file[register] = (value,valid)
void write(std::string register, int value, bool valid){

}

//Get reg_file[register] value
//WARNING: Does NOT perform any membership test
int read(std::string register){

}

//Check reg_file[register] validity
//WARNING: Does not perform any membership test
bool isValid(std::string register){

}
