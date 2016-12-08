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
#include <stdexcept>
#include <queue>

#ifndef REGISTER_H
#define REGISTER_H

class Registers
{
private:
  //register := {string name:(int value, bool valid)}
  std::map<std::string, std::tuple<int,bool>> reg_file;

  //Front end table := {string pReg, string rReg}
  std::map<std::string, std::string> front_end;

  //Back end table := {string rReg, string pReg}
  std::map<std::string, std::string> back_end;

  //holds list of physical registers that are ready to to be used
  std::queue<std::string> free_list;

  //Number of physical registers, default=32
  int num_reg = 32;

public:
  Registers(); //initialize the RF with all registers/flags set to zero

  ~Registers(); //deconstructor

  //methods for simulator's interface control
  void initialize(); //reset the RF with all registers/flags set to zero
  void display(); //display the contents of the registers/flags

  //create instance of R reg
  std::string getRenamed(std::string);

  //TODO create function that updates back_end list
  void commit(std::string pReg);
  //TODO create function to release physical registers
  //TODO

  //methods for interacting with the register file map
  void write(std::string reg, int value, bool valid); //sets reg_file[register] = (value,valid)
  int physRead(std::string reg); //get reg_file[register] value
  bool physIsValid(std::string reg); //get reg_file[register] validity

  //void write(std::string reg, int value, bool valid); //sets reg_file[register] = (value,valid)
  int read(std::string reg); //take R reg, get P reg, call to get value
  bool isValid(std::string reg); //take R reg, get P reg, call to get validity

  //method to set the number of physical registers in processor
  void setNumReg(int num); //sets phy_reg = num (default = 32)
};

#endif
