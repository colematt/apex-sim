/* FILE INFORMATION
File:     register.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: header file for register.cpp
*/
#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <tuple>
#include <exception>

#ifndef REGISTER_H
#define REGISTER_H

#define NUM_REGS 16 //number of registers in this ISA

class Registers
{
private:
  //register := {string name:(int value, bool valid)}
  std::map<std::string, std::tuple<int,bool>> reg_file;

public:
  Registers(); //initialize the RF with all registers/flags set to zero

  //methods for simulator's interface control
  void initialize(); //reset the RF with all registers/flags set to zero
  void display(); //display the contents of the registers/flags

  //methods for interacting with the register file map
  void write(std::string register, int value, bool valid); //sets reg_file[register] = (value,valid)
  int read(std::string register); //get reg_file[register] value
  bool isValid(std::string register); //get reg_file[register] validity
};

#endif
