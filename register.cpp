/* FILE INFORMATION
File:     register.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the Registers class, which simulates operation of a register file.
*/

class Registers
{
private:
  std::map<std::string,short> values;
  std::map<std::string,bool> valids;
public:
  RegisterFile(); //initialize the RF with all registers/flags set to zero

  void initialize(); //reset the RF with all registers/flags set to zero
  void display(); //display the contents of the registers/flags

  //methods for interacting with values map
  void write(string register, int value); //sets values[register] = value
  int read(string register); //return values[register]

  //methods for interacting with valid map
  void setValid(string register, bool valid); //set valids[register] = valid
  void flipValid(string register); //set valids[register] = !valids[register]
  bool getValid(string register); //return valids[register]
}
