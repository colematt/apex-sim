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

#ifndef REGISTER_H
#define REGISTER_H

class Registers
{
private:
  std::map<std::string,int> reg_file;

public:
  Registers(); //initialize the RF with all registers/flags set to zero

  void initialize(); //reset the RF with all registers/flags set to zero
  void display(); //display the contents of the registers/flags

  //methods for interacting with values map
  void write(string register, int value, bool valid); //sets values[register] = (value,valid)
  int read(string register); //return values[register]
};

#endif
