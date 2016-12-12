/* FILE INFORMATION
File:     data.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the DATA class, which simulates reading and writing main memory
*/

#include "data.h"
#include <iostream>

  Data::Data(){ //initialize the memory with all positions set to zero
    this->initialize();
  }

  Data::~Data(){

  }

  //Initialize vector size and vector positions
  void Data::initialize(){
    memory.resize(4000);

    for (int i = 0; i < memory.size(); i++){
      memory.at(i) = 0;
    }
  }

  //Read four bytes from memory starting at address <addr>
  int Data::readMem(int addr){
    return memory.at(addr);
  }

  //Write four bytes to memory starting at <addr>
  void Data::writeMem(int addr, int value){
    memory.at(addr) = value;
  }

  //Display addressable contents of memory from a1 to a2 inclusive
  void Data::display(int a1, int a2){
    // Assert alignment with addressable bounds
    a1 = a1 - (a1 % 4);
    a2 = a2 - (a2 % 4);

    if (VERBOSE >= 1)
      std::cout << "Address: Value" << std::endl;

    //Display contents at address
    for (int addr = a1; addr <= a2; addr += 4){
        std::cout << addr << ": " << memory.at(addr) << std::endl;
    }
  } //end display()
