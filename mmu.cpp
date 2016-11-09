/* FILE INFORMATION
File:     mmu.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the MMU class, which simulates reading and writing main memory, and reading instructions from the program
*/
#include "mmu.h"

class MMU
{
private:

public:
  MMU(const char* codeFile);
  ~MMU();

  //Read in all instructions from file
  void readCode(){
    //Read file line by line
    //Parse line into instruction_t
    //Put instruction_t generated into holder vector
  }

  //Get instruction given index of instruction pointer
  instruction_t getInstr(int addr){

  }

  //Read one byte-address from memory at <addr>
  int readMem(int addr);

  //Write one byte to memory at <addr>
  void writeMem(int addr, int value);

  //Display contents of memory beginning at <startAddr>
  //and ending at <endAddr>, inclusive
  //If <endAddr> < <startAddr>, return silently.
  void display(int startAddr, int endAddr);

};
