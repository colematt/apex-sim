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
#include <vector>

#ifndef REGISTER_H
#define REGISTER_H

class Registers
{
private:
  struct CompareString {
    bool operator()(std::string const &s1, std::string const &s2){
      std::string s1m = s1, s2m = s2;

      s1m.erase(0,1); s2m.erase(0,1);

      int i1 = std::stoi (s1m), i2 = std::stoi (s2m);

      return i1 > i2;
    }
  };

  //register := {string name:(int value, bool valid)}
  std::map<std::string, std::tuple<int,bool>> reg_file;

  //Front end table := {string pReg, string rReg}
  std::map<std::string, std::string> front_end;

  //Back end table := {string rReg, string pReg}
  std::map<std::string, std::string> back_end;

  //holds list of physical registers that are ready to to be used
  std::priority_queue<std::string, std::vector<std::string>, CompareString> free_list;

  //Number of physical registers, default=32
  int num_reg = 32;

public:
  Registers(); //initialize the RF with all registers/flags set to zero

  ~Registers(); //deconstructor

  //methods for simulator's interface control
  void initialize(); //reset the RF with all registers/flags set to zero

  void dUrf(); //Display contents of unified registers
  void dMap(); //Display Front end and Back end rename tables

  //create instance of R reg
  std::string getRenamed(std::string);

  //Updates back_end list
  //Releases physical registers
  void commit(std::string pReg);

  bool deallocate(std::string reg); //Return true on action, false on no action

  //methods for interacting with the register file map
  void write(std::string reg, int value, bool valid); //sets reg_file[register] = (value,valid)
  int physRead(std::string reg); //get reg_file[register] value
  bool physIsValid(std::string reg); //get reg_file[register] validity

  //void write(std::string reg, int value, bool valid); //sets reg_file[register] = (value,valid)
  int read(std::string reg); //take R reg, get P reg, call to get value
  bool isValid(std::string reg); //take R reg, get P reg, call to get validity

  //method to set the number of physical registers in processor
  void setNumReg(int num); //sets phy_reg = num (default = 32)

  std::string translateReg(std::string pReg); //Translates P reg to R reg for forwarding compares.

};

#endif
